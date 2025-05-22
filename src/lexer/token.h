#ifndef SQL_INTERPRETER_LEXER_TOKEN_H
#define SQL_INTERPRETER_LEXER_TOKEN_H

#include <string>
#include <variant> // Ensure std::variant is available
#include <cstddef> // For std::nullptr_t

namespace sql_interpreter {
namespace lexer {

// Enum for different types of tokens
enum class TokenType {
    // Keywords
    SELECT, FROM, WHERE, INSERT, INTO, VALUES, CREATE, TABLE, AS, AND, OR, NOT,
    // Identifiers (table names, column names, etc.)
    IDENTIFIER,
    // Literals
    STRING_LITERAL,
    NUMERIC_LITERAL,
    BOOLEAN_LITERAL, // true, false
    NULL_LITERAL,    // NULL
    // Operators
    EQUAL,          // =
    NOT_EQUAL,      // != or <>
    LESS_THAN,      // <
    GREATER_THAN,   // >
    LESS_EQUAL,     // <=
    GREATER_EQUAL,  // >=
    PLUS,           // +
    MINUS,          // -
    MULTIPLY,       // *
    DIVIDE,         // /
    MODULO,         // %
    // Punctuation
    LEFT_PAREN,     // (
    RIGHT_PAREN,    // )
    COMMA,          // ,
    SEMICOLON,      // ;
    DOT,            // .
    // Special
    END_OF_FILE,    // EOF
    UNKNOWN         // Unrecognized token
};

// Helper function to convert TokenType to string (for debugging)
std::string tokenTypeToString(TokenType type);

// Represents a single token
struct Token {
    TokenType type;
    std::string lexeme; // The actual string value of the token
    // Using std::variant for literal values to store different types (string, double, bool, nullptr_t)
    // For simplicity, you might start with just std::string and parse later, or use a more complex system.
    std::variant<std::string, double, bool, std::nullptr_t> literal; 
    int line;           // Line number where the token appears
    int column;         // Column number where the token begins

    Token(TokenType type, const std::string& lexeme, int line, int col, 
          std::variant<std::string, double, bool, std::nullptr_t> literal_val = std::nullptr_t())
        : type(type), lexeme(lexeme), literal(literal_val), line(line), column(col) {}

    std::string toString() const;
};

} // namespace lexer
} // namespace sql_interpreter

#endif // SQL_INTERPRETER_LEXER_TOKEN_H
