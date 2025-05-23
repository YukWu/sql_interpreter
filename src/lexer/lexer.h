#ifndef SQL_INTERPRETER_LEXER_LEXER_H
#define SQL_INTERPRETER_LEXER_LEXER_H

#include "token.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace sql_interpreter {
namespace lexer {

class Lexer {
public:
    explicit Lexer(const std::string& source);
    
    // 主要的词法分析方法
    std::vector<Token> tokenize();
    
private:
    std::string source_;
    size_t current_;
    size_t line_;
    size_t column_;
    
    // 关键字映射表
    static const std::unordered_map<std::string, TokenType> keywords_;
    
    // 辅助方法
    bool isAtEnd() const;
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char expected);
    void skipWhitespace();
    
    // 词素扫描方法
    Token scanToken();
    Token string(char quote);
    Token number();
    Token identifier();
    
    // 字符判断方法
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    bool isAlphaNumeric(char c) const;
    
    // 错误处理
    Token errorToken(const std::string& message);
};

} // namespace lexer
} // namespace sql_interpreter

#endif // SQL_INTERPRETER_LEXER_LEXER_H
