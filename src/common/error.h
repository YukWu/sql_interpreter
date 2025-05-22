#ifndef SQL_INTERPRETER_COMMON_ERROR_H
#define SQL_INTERPRETER_COMMON_ERROR_H

#include <string>
#include <stdexcept> // For std::runtime_error

namespace sql_interpreter {
namespace common {

// Enum for different types of errors
enum class ErrorType {
    LEXICAL_ERROR,
    SYNTAX_ERROR,
    SEMANTIC_ERROR, // Placeholder for future use
    RUNTIME_ERROR   // Placeholder for future use
};

// Basic Error class
class Error : public std::runtime_error {
public:
    Error(ErrorType type, const std::string& message, int line = -1, int column = -1)
        : std::runtime_error(message), errorType_(type), line_(line), column_(column) {}

    ErrorType getErrorType() const { return errorType_; }
    int getLine() const { return line_; }
    int getColumn() const { return column_; }

    std::string format() const {
        std::string typeStr;
        switch (errorType_) {
            case ErrorType::LEXICAL_ERROR: typeStr = "LexicalError"; break;
            case ErrorType::SYNTAX_ERROR:  typeStr = "SyntaxError";  break;
            case ErrorType::SEMANTIC_ERROR:typeStr = "SemanticError";break;
            case ErrorType::RUNTIME_ERROR: typeStr = "RuntimeError"; break;
            default: typeStr = "UnknownError";
        }
        std::string posStr = (line_ != -1 && column_ != -1)
                           ? " [at " + std::to_string(line_) + ":" + std::to_string(column_) + "]"
                           : "";
        return typeStr + ":" + posStr + " " + what();
    }

private:
    ErrorType errorType_;
    int line_;
    int column_;
};

// Specific error types (optional, can be added as needed)
class LexicalError : public Error {
public:
    LexicalError(const std::string& message, int line = -1, int column = -1)
        : Error(ErrorType::LEXICAL_ERROR, message, line, column) {}
};

class SyntaxError : public Error {
public:
    SyntaxError(const std::string& message, int line = -1, int column = -1)
        : Error(ErrorType::SYNTAX_ERROR, message, line, column) {}
};

} // namespace common
} // namespace sql_interpreter

#endif // SQL_INTERPRETER_COMMON_ERROR_H
