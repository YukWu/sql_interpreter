# C++ SQL Interpreter

This project is a C++ implementation of a SQL interpreter, focusing on parsing SQL queries and converting them into Abstract Syntax Trees (ASTs).

## Modules

-   **Lexer**: Tokenizes the input SQL string into a stream of tokens.
-   **Parser**: Constructs an AST from the token stream based on SQL grammar.
-   **AST Nodes**: Defines the structure of the AST.
-   **Error Handling**: Manages and reports parsing errors.
-   **Interpreter Interface**: Provides the main entry point for parsing SQL queries.

## Features

### Current Features
- ✅ **SQL Lexical Analysis**: Complete lexer implementation that tokenizes SQL statements
- ✅ **Token Types**: Support for keywords, identifiers, literals, operators, and punctuation
- ✅ **Error Handling**: Basic error reporting for invalid tokens
- ✅ **Position Tracking**: Line and column tracking for better error messages

### Planned Features
- 🔲 **SQL Parser**: Convert token stream to Abstract Syntax Tree (AST)

## Project Structure

```
sql_interpreter/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── build/                # CMake build directory (created by user)
├── src/
│   ├── ast/
│   │   └── ast_node.h    # AST node base class
│   ├── common/
│   │   └── error.h       # Error handling classes
│   ├── lexer/
│   │   ├── token.h       # Token definition
│   │   ├── token.cpp     # Token helper functions
│   │   ├── lexer.h       # Lexer class definition
│   │   └── lexer.cpp     # Lexer implementation
│   ├── parser/           # Parser implementation (to be added)
│   ├── interpreter.h     # Main interpreter interface (to be added)
│   └── interpreter.cpp   # Main interpreter implementation (to be added)
├── include/              # Public headers (if any, currently unused)
├── docs/                 # Documentation
│   └── lexer_usage.md    # Lexer usage documentation
├── tests/                # Unit tests (to be added)
└── examples/
    └── main.cpp          # Example usage
```

## Getting Started

### Prerequisites

-   C++17 compatible compiler (e.g., GCC, Clang)
-   CMake (version 3.10 or higher)

### Building the Project

1.  **Clone the repository (if you haven't already):**
    ```bash
    # git clone <repository-url>
    # cd sql_interpreter
    ```

2.  **Create a build directory and navigate into it:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the project with CMake:**
    ```bash
    cmake ..
    ```

4.  **Build the project:**
    ```bash
    make
    ```
    Alternatively, you can use:
    ```bash
    cmake --build .
    ```

5.  **Run the example executable (from the `build` directory):**
    ```bash
    ./sql_interpreter_example
    ```

## Usage Examples

### Basic Lexer Usage

```cpp
#include "lexer/lexer.h"

int main() {
    // Create a lexer instance with SQL input
    std::string sql = "SELECT name, age FROM users WHERE id = 123;";
    sql_interpreter::lexer::Lexer lexer(sql);
    
    // Tokenize the SQL string
    auto tokens = lexer.tokenize();
    
    // Process the tokens
    for (const auto& token : tokens) {
        std::cout << token.toString() << std::endl;
    }
    
    return 0;
}
```

### Supported SQL Statements

The lexer currently supports tokenization of:

- **SELECT statements**: `SELECT column1, column2 FROM table WHERE condition;`
- **INSERT statements**: `INSERT INTO table (col1, col2) VALUES (val1, val2);`
- **CREATE TABLE statements**: `CREATE TABLE name (col1 TYPE, col2 TYPE);`
- **Complex conditions**: Support for operators like `>=`, `!=`, `AND`, `OR`

### Example Output

For the SQL statement:
```sql
SELECT name FROM users WHERE age >= 18 AND active = true;
```

The lexer produces:
```
Token[SELECT, 'SELECT', L:1, C:1]
Token[IDENTIFIER, 'name' ('name'), L:1, C:8]
Token[FROM, 'FROM', L:1, C:13]
Token[IDENTIFIER, 'users' ('users'), L:1, C:18]
Token[WHERE, 'WHERE', L:1, C:24]
Token[IDENTIFIER, 'age' ('age'), L:1, C:30]
Token[GREATER_EQUAL, '>=', L:1, C:34]
Token[NUMERIC_LITERAL, '18' (18.000000), L:1, C:37]
Token[AND, 'AND', L:1, C:40]
Token[IDENTIFIER, 'active' ('active'), L:1, C:44]
Token[EQUAL, '=', L:1, C:51]
Token[BOOLEAN_LITERAL, 'true' (true), L:1, C:53]
Token[SEMICOLON, ';', L:1, C:57]
Token[END_OF_FILE, '', L:1, C:58]
```

## Documentation

- [Lexer Usage Guide](docs/lexer_usage.md) - Detailed documentation for the lexer component

## Contributing

(Contribution guidelines will be added here.)
