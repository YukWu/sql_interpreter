#ifndef SQL_INTERPRETER_AST_AST_NODE_H
#define SQL_INTERPRETER_AST_AST_NODE_H

#include <string>
#include <vector>
#include <memory> // For std::unique_ptr or std::shared_ptr

namespace sql_interpreter {
namespace ast {

// Forward declaration for potential circular dependencies if nodes reference each other
// class SomeOtherNode;

// Enum to represent the type of an AST node
enum class ASTNodeType {
    // Statements
    SELECT_STATEMENT,
    INSERT_STATEMENT,
    CREATE_TABLE_STATEMENT,
    // Clauses
    FROM_CLAUSE,
    WHERE_CLAUSE,
    // Expressions
    LITERAL,
    IDENTIFIER,
    BINARY_EXPRESSION,
    FUNCTION_CALL,
    // Add more types as needed
    UNKNOWN // Default or error type
};

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default; // Important for proper cleanup of derived classes

    // Pure virtual function to get the type of the node
    virtual ASTNodeType getType() const = 0;

    // Optional: virtual function to get a string representation (for debugging/printing)
    virtual std::string toString(int indent = 0) const {
        return std::string(indent, ' ') + "ASTNode (Unknown)";
    }

    // Optional: line and column numbers for error reporting
    int line = -1;
    int column = -1;

    // Children nodes - using unique_ptr for ownership
    // Alternatively, use std::vector<std::shared_ptr<ASTNode>> if shared ownership is needed
    std::vector<std::unique_ptr<ASTNode>> children;

protected:
    // Helper for toString in derived classes
    std::string indentString(int indent) const {
        return std::string(indent, ' ');
    }
};

} // namespace ast
} // namespace sql_interpreter

#endif // SQL_INTERPRETER_AST_AST_NODE_H
