#include "token.h"
#include <stdexcept> // For std::out_of_range in a more complex scenario

namespace sql_interpreter {
namespace lexer {

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::SELECT: return "SELECT";
        case TokenType::FROM: return "FROM";
        case TokenType::WHERE: return "WHERE";
        case TokenType::INSERT: return "INSERT";
        case TokenType::INTO: return "INTO";
        case TokenType::VALUES: return "VALUES";
        case TokenType::CREATE: return "CREATE";
        case TokenType::TABLE: return "TABLE";
        case TokenType::AS: return "AS";
        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";
        case TokenType::NOT: return "NOT";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::NUMERIC_LITERAL: return "NUMERIC_LITERAL";
        case TokenType::BOOLEAN_LITERAL: return "BOOLEAN_LITERAL";
        case TokenType::NULL_LITERAL: return "NULL_LITERAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::LESS_THAN: return "LESS_THAN";
        case TokenType::GREATER_THAN: return "GREATER_THAN";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::DIVIDE: return "DIVIDE";
        case TokenType::MODULO: return "MODULO";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::COMMA: return "COMMA";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::DOT: return "DOT";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        case TokenType::UNKNOWN: return "UNKNOWN";
        default: return "<Unknown TokenType>";
    }
}

std::string Token::toString() const {
    std::string literalStr = "";
    if (std::holds_alternative<std::string>(literal)) {
        literalStr = " ('" + std::get<std::string>(literal) + "')";
    } else if (std::holds_alternative<double>(literal)) {
        literalStr = " (" + std::to_string(std::get<double>(literal)) + ")";
    } else if (std::holds_alternative<bool>(literal)) {
        literalStr = std::get<bool>(literal) ? " (true)" : " (false)";
    } else if (std::holds_alternative<std::nullptr_t>(literal) && type == TokenType::NULL_LITERAL) {
        literalStr = " (NULL)";
    }

    return "Token[" + tokenTypeToString(type) + ", '" + lexeme + "'" + literalStr +
           ", L:" + std::to_string(line) + ", C:" + std::to_string(column) + "]";
}

} // namespace lexer
} // namespace sql_interpreter
