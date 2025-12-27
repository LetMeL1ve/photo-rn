#pragma once
#include <string>

// Enumeration for type of token.
enum class TokenType {
    PLACEHOLDER,
    LITERAL
};

class Token {
private:
    TokenType type;  // Type of token.
    std::string text;  // Text of token.
public:
    // Getters
    TokenType get_type() const { return type; }
    std::string get_text() const { return text; }

    // Constructor
    Token(TokenType _type, const std::string& _text) : type(_type), text(_text) {};
};