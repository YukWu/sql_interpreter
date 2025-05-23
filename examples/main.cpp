#include <iostream>
#include "lexer/token.h" // Include token header
#include "lexer/lexer.h" // Include the new Lexer class
#include "common/error.h" // Include error header

int main() {
    // 测试基本的 Token
    sql_interpreter::lexer::Token token(sql_interpreter::lexer::TokenType::SELECT, "SELECT", 1, 1);
    std::cout << "Hello from SQL Interpreter example!" << std::endl;
    std::cout << "Token: " << token.toString() << std::endl;

    // 测试 Lexer 类
    std::vector<std::string> testCases = {
        "SELECT name, age FROM users WHERE id = 123 AND active = true;",
        "INSERT INTO products (name, price) VALUES ('Laptop', 999.99);",
        "CREATE TABLE students (id INTEGER, name STRING, grade DOUBLE);",
        "SELECT * FROM orders WHERE total >= 100.0 AND status != 'cancelled';"
    };
    
    for (const auto& sql : testCases) {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "Tokenizing SQL: " << sql << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        
        sql_interpreter::lexer::Lexer lexer(sql);
        auto tokens = lexer.tokenize();
        
        std::cout << "Tokens found: " << tokens.size() << std::endl;
        for (const auto& t : tokens) {
            std::cout << t.toString() << std::endl;
        }
    }

    try {
        // Example of using the error class
        // throw sql_interpreter::common::SyntaxError("Unexpected token", 2, 5);
    } catch (const sql_interpreter::common::Error& e) {
        std::cerr << e.format() << std::endl;
        return 1;
    }
    return 0;
}
