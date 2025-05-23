#include "lexer.h"
#include <cctype>
#include <algorithm>

namespace sql_interpreter {
namespace lexer {

// 静态关键字映射表
const std::unordered_map<std::string, TokenType> Lexer::keywords_ = {
    {"SELECT", TokenType::SELECT},
    {"FROM", TokenType::FROM},
    {"WHERE", TokenType::WHERE},
    {"INSERT", TokenType::INSERT},
    {"INTO", TokenType::INTO},
    {"VALUES", TokenType::VALUES},
    {"CREATE", TokenType::CREATE},
    {"TABLE", TokenType::TABLE},
    {"AS", TokenType::AS},
    {"AND", TokenType::AND},
    {"OR", TokenType::OR},
    {"NOT", TokenType::NOT},
    {"TRUE", TokenType::BOOLEAN_LITERAL},
    {"FALSE", TokenType::BOOLEAN_LITERAL},
    {"NULL", TokenType::NULL_LITERAL}
};

Lexer::Lexer(const std::string& source) 
    : source_(source), current_(0), line_(1), column_(1) {
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    
    while (!isAtEnd()) {
        Token token = scanToken();
        // 只添加非 UNKNOWN 的 token，或者有实际内容的 UNKNOWN token
        if (token.type != TokenType::UNKNOWN || !token.lexeme.empty()) {
            tokens.push_back(token);
        }
    }
    
    tokens.emplace_back(TokenType::END_OF_FILE, "", line_, column_);
    return tokens;
}

bool Lexer::isAtEnd() const {
    return current_ >= source_.length();
}

char Lexer::advance() {
    if (isAtEnd()) return '\0';
    
    char c = source_[current_++];
    if (c == '\n') {
        line_++;
        column_ = 1;
    } else {
        column_++;
    }
    return c;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source_[current_];
}

char Lexer::peekNext() const {
    if (current_ + 1 >= source_.length()) return '\0';
    return source_[current_ + 1];
}

bool Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (source_[current_] != expected) return false;
    
    advance();
    return true;
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\r' || c == '\t' || c == '\n') {
            advance();
        } else {
            break;
        }
    }
}

Token Lexer::scanToken() {
    skipWhitespace();
    
    if (isAtEnd()) {
        // 不在这里返回 END_OF_FILE，让 tokenize() 统一处理
        return Token(TokenType::UNKNOWN, "", line_, column_);
    }
    
    size_t startColumn = column_;
    char c = advance();
    
    switch (c) {
        case '(': return Token(TokenType::LEFT_PAREN, "(", line_, startColumn);
        case ')': return Token(TokenType::RIGHT_PAREN, ")", line_, startColumn);
        case ',': return Token(TokenType::COMMA, ",", line_, startColumn);
        case ';': return Token(TokenType::SEMICOLON, ";", line_, startColumn);
        case '.': return Token(TokenType::DOT, ".", line_, startColumn);
        case '+': return Token(TokenType::PLUS, "+", line_, startColumn);
        case '-': return Token(TokenType::MINUS, "-", line_, startColumn);
        case '*': return Token(TokenType::MULTIPLY, "*", line_, startColumn);
        case '/': return Token(TokenType::DIVIDE, "/", line_, startColumn);
        case '%': return Token(TokenType::MODULO, "%", line_, startColumn);
        case '=': return Token(TokenType::EQUAL, "=", line_, startColumn);
        case '<':
            if (match('=')) {
                return Token(TokenType::LESS_EQUAL, "<=", line_, startColumn);
            } else if (match('>')) {
                return Token(TokenType::NOT_EQUAL, "<>", line_, startColumn);
            } else {
                return Token(TokenType::LESS_THAN, "<", line_, startColumn);
            }
        case '>':
            if (match('=')) {
                return Token(TokenType::GREATER_EQUAL, ">=", line_, startColumn);
            } else {
                return Token(TokenType::GREATER_THAN, ">", line_, startColumn);
            }
        case '!':
            if (match('=')) {
                return Token(TokenType::NOT_EQUAL, "!=", line_, startColumn);
            } else {
                return errorToken("Unexpected character '!'");
            }
        case '\'':
        case '"':
            return string(c);
        default:
            if (isDigit(c)) {
                // 回退一个字符，让 number() 方法处理完整的数字
                current_--;
                column_--;
                return number();
            } else if (isAlpha(c)) {
                // 回退一个字符，让 identifier() 方法处理完整的标识符
                current_--;
                column_--;
                return identifier();
            } else {
                return errorToken("Unexpected character: " + std::string(1, c));
            }
    }
}

Token Lexer::string(char quote) {
    size_t startColumn = column_ - 1; // 调整起始列，因为引号已经被消费
    std::string value;
    std::string lexeme;
    lexeme += quote;
    
    while (peek() != quote && !isAtEnd()) {
        char c = advance();
        value += c;
        lexeme += c;
    }
    
    if (isAtEnd()) {
        return errorToken("Unterminated string");
    }
    
    // 消费结束引号
    advance();
    lexeme += quote;
    
    return Token(TokenType::STRING_LITERAL, lexeme, line_, startColumn, value);
}

Token Lexer::number() {
    size_t startColumn = column_;
    std::string lexeme;
    
    // 收集整数部分
    while (isDigit(peek())) {
        lexeme += advance();
    }
    
    // 查看是否有小数点
    if (peek() == '.' && isDigit(peekNext())) {
        lexeme += advance(); // 消费小数点
        
        // 收集小数部分
        while (isDigit(peek())) {
            lexeme += advance();
        }
    }
    
    double value = std::stod(lexeme);
    return Token(TokenType::NUMERIC_LITERAL, lexeme, line_, startColumn, value);
}

Token Lexer::identifier() {
    size_t startColumn = column_;
    std::string lexeme;
    
    // 收集标识符字符
    while (isAlphaNumeric(peek()) || peek() == '_') {
        lexeme += advance();
    }
    
    // 转换为大写以检查关键字
    std::string upperLexeme = lexeme;
    std::transform(upperLexeme.begin(), upperLexeme.end(), 
                   upperLexeme.begin(), ::toupper);
    
    // 检查是否是关键字
    auto it = keywords_.find(upperLexeme);
    if (it != keywords_.end()) {
        TokenType type = it->second;
        
        if (type == TokenType::BOOLEAN_LITERAL) {
            bool value = (upperLexeme == "TRUE");
            return Token(type, lexeme, line_, startColumn, value);
        } else if (type == TokenType::NULL_LITERAL) {
            return Token(type, lexeme, line_, startColumn, nullptr);
        } else {
            return Token(type, lexeme, line_, startColumn);
        }
    }
    
    // 不是关键字，返回标识符
    return Token(TokenType::IDENTIFIER, lexeme, line_, startColumn, lexeme);
}

bool Lexer::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           c == '_';
}

bool Lexer::isAlphaNumeric(char c) const {
    return isAlpha(c) || isDigit(c);
}

Token Lexer::errorToken(const std::string& message) {
    return Token(TokenType::UNKNOWN, message, line_, column_);
}

} // namespace lexer
} // namespace sql_interpreter
