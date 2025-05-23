#include <catch2/catch_test_macros.hpp>
#include "lexer/lexer.h"

using namespace sql_interpreter::lexer;

TEST_CASE("Basic SQL tokenization", "[lexer]") {
    Lexer lexer("SELECT name FROM users;");
    auto tokens = lexer.tokenize();
    
    REQUIRE(tokens.size() == 6);
    CHECK(tokens[0].type == TokenType::SELECT);
    CHECK(tokens[0].lexeme == "SELECT");
    CHECK(tokens[1].type == TokenType::IDENTIFIER);
    CHECK(tokens[1].lexeme == "name");
    CHECK(tokens[2].type == TokenType::FROM);
    CHECK(tokens[2].lexeme == "FROM");
    CHECK(tokens[3].type == TokenType::IDENTIFIER);
    CHECK(tokens[3].lexeme == "users");
    CHECK(tokens[4].type == TokenType::SEMICOLON);
    CHECK(tokens[4].lexeme == ";");
    CHECK(tokens[5].type == TokenType::END_OF_FILE);
}

TEST_CASE("String literals tokenization", "[lexer][strings]") {
    Lexer lexer("INSERT INTO users VALUES ('John', \"Doe\");");
    auto tokens = lexer.tokenize();
    
    bool foundSingleQuote = false, foundDoubleQuote = false;
    for (const auto& token : tokens) {
        if (token.type == TokenType::STRING_LITERAL) {
            if (token.lexeme == "'John'") foundSingleQuote = true;
            if (token.lexeme == "\"Doe\"") foundDoubleQuote = true;
        }
    }
    
    CHECK(foundSingleQuote);
    CHECK(foundDoubleQuote);
}

TEST_CASE("Numeric literals tokenization", "[lexer][numbers]") {
    Lexer lexer("SELECT * WHERE age = 25 AND price = 99.99;");
    auto tokens = lexer.tokenize();
    
    bool foundInteger = false, foundFloat = false;
    for (const auto& token : tokens) {
        if (token.type == TokenType::NUMERIC_LITERAL) {
            if (token.lexeme == "25") foundInteger = true;
            if (token.lexeme == "99.99") foundFloat = true;
        }
    }
    
    CHECK(foundInteger);
    CHECK(foundFloat);
}

TEST_CASE("Operators tokenization", "[lexer][operators]") {
    Lexer lexer("WHERE a >= 10 AND b != 'test' AND c <> 5;");
    auto tokens = lexer.tokenize();
    
    bool foundGE = false, foundNE1 = false, foundNE2 = false;
    for (const auto& token : tokens) {
        if (token.lexeme == ">=") foundGE = true;
        if (token.lexeme == "!=") foundNE1 = true;
        if (token.lexeme == "<>") foundNE2 = true;
    }
    
    CHECK(foundGE);
    CHECK(foundNE1);
    CHECK(foundNE2);
}

TEST_CASE("Boolean and null literals", "[lexer][literals]") {
    Lexer lexer("SELECT * WHERE active = true AND deleted = false AND data = NULL;");
    auto tokens = lexer.tokenize();
    
    bool foundTrue = false, foundFalse = false, foundNull = false;
    for (const auto& token : tokens) {
        if (token.type == TokenType::BOOLEAN_LITERAL) {
            if (token.lexeme == "true") foundTrue = true;
            if (token.lexeme == "false") foundFalse = true;
        }
        if (token.type == TokenType::NULL_LITERAL) {
            foundNull = true;
        }
    }
    
    CHECK(foundTrue);
    CHECK(foundFalse);
    CHECK(foundNull);
}

TEST_CASE("Complex SQL statement", "[lexer][complex]") {
    Lexer lexer("INSERT INTO products VALUES ('iPhone', 199.99, true) WHERE name = 'phone';");
    auto tokens = lexer.tokenize();
    
    // Check that we have the expected keywords
    bool foundInsert = false, foundInto = false, foundValues = false, foundWhere = false;
    for (const auto& token : tokens) {
        if (token.type == TokenType::INSERT) foundInsert = true;
        if (token.type == TokenType::INTO) foundInto = true;
        if (token.type == TokenType::VALUES) foundValues = true;
        if (token.type == TokenType::WHERE) foundWhere = true;
    }
    
    CHECK(foundInsert);
    CHECK(foundInto);
    CHECK(foundValues);
    CHECK(foundWhere);
}
#include <iostream>
TEST_CASE("Empty and whitespace handling", "[lexer][edge-cases]") {
    SECTION("Empty string") {
        Lexer lexer("");
        auto tokens = lexer.tokenize();
        REQUIRE(tokens.size() == 1);
        CHECK(tokens[0].type == TokenType::END_OF_FILE);
    }
    
    SECTION("Only whitespace") {
        Lexer lexer("   \t\n   ");
        auto tokens = lexer.tokenize();
        for(auto& token : tokens) {
            std::cout << token.toString() << std::endl;
        }
        REQUIRE(tokens.size() == 1);
        
        CHECK(tokens[0].type == TokenType::END_OF_FILE);
    }
}

TEST_CASE("Case insensitive keywords", "[lexer][keywords]") {
    Lexer lexer("select Name from Users where Age > 25;");
    auto tokens = lexer.tokenize();
    
    CHECK(tokens[0].type == TokenType::SELECT);
    CHECK(tokens[0].lexeme == "select");
    CHECK(tokens[2].type == TokenType::FROM);
    CHECK(tokens[2].lexeme == "from");
    CHECK(tokens[4].type == TokenType::WHERE);
    CHECK(tokens[4].lexeme == "where");
}
