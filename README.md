# C++ SQL Interpreter

This project is a C++ implementation of a SQL interpreter, focusing on parsing SQL queries and converting them into Abstract Syntax Trees (ASTs).

## Modules

-   **Lexer**: Tokenizes the input SQL string.
-   **Parser**: Constructs an AST from the token stream based on SQL grammar.
-   **AST Nodes**: Defines the structure of the AST.
-   **Error Handling**: Manages and reports parsing errors.
-   **Interpreter Interface**: Provides the main entry point for parsing SQL queries.

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
│   │   └── token.cpp     # Token helper functions
│   ├── parser/           # Parser implementation (to be added)
│   ├── interpreter.h     # Main interpreter interface (to be added)
│   └── interpreter.cpp   # Main interpreter implementation (to be added)
├── include/              # Public headers (if any, currently unused)
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

## Contributing

(Contribution guidelines will be added here.)
