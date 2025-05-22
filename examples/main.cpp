#include <iostream>
#include "../src/lexer/token.h" // Example include
#include "../src/common/error.h" // Example include

int main() {
    sql_interpreter::lexer::Token token(sql_interpreter::lexer::TokenType::SELECT, "SELECT", 1, 1);
    std::cout << "Hello from SQL Interpreter example!" << std::endl;
    std::cout << "Token: " << token.toString() << std::endl;

    try {
        // Example of using the error class
        // throw sql_interpreter::common::SyntaxError("Unexpected token", 2, 5);
    } catch (const sql_interpreter::common::Error& e) {
        std::cerr << e.format() << std::endl;
        return 1;
    }
    return 0;
}
