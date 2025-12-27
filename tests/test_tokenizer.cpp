#include <catch2/catch_test_macros.hpp>
#include "generator/tokenizer/tokenizer.hpp"

TEST_CASE("get_tokens - literal only") {
    std::vector<Token> tokens;
    get_tokens("abc", tokens);
    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].get_type() == TokenType::LITERAL);
    REQUIRE(tokens[0].get_text() == "abc");
}

TEST_CASE("get_tokens - single placeholder") {
    std::vector<Token> tokens;
    get_tokens("{date}", tokens);
    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[0].get_text() == "date");
}

TEST_CASE("get_tokens - mixed") {
    std::vector<Token> tokens;
    get_tokens("img_{seq}.{ext}", tokens);
    REQUIRE(tokens.size() == 4);

    REQUIRE(tokens[0].get_type() == TokenType::LITERAL);
    REQUIRE(tokens[0].get_text() == "img_");

    REQUIRE(tokens[1].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[1].get_text() == "seq");

    REQUIRE(tokens[2].get_type() == TokenType::LITERAL);
    REQUIRE(tokens[2].get_text() == ".");

    REQUIRE(tokens[3].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[3].get_text() == "ext");
}

TEST_CASE("get_tokens - invalid patterns throw") {
    std::vector<Token> tokens;
    REQUIRE_THROWS(get_tokens("{date", tokens));
    REQUIRE_THROWS(get_tokens("date}", tokens));
    REQUIRE_THROWS(get_tokens("{unknown}", tokens));
}

TEST_CASE("get_tokens - empty placeholder skipped") {
    std::vector<Token> tokens;
    get_tokens("a{}b", tokens);
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].get_text() == "a");
    REQUIRE(tokens[1].get_text() == "b");
}

TEST_CASE("get_tokens - empty pattern yields no tokens") {
    std::vector<Token> tokens;
    get_tokens("", tokens);
    REQUIRE(tokens.empty());
}

TEST_CASE("get_tokens - only empty braces yields no tokens") {
    std::vector<Token> tokens;
    get_tokens("{}", tokens);
    REQUIRE(tokens.empty());
}

TEST_CASE("get_tokens - placeholder at start then literal") {
    std::vector<Token> tokens;
    get_tokens("{date}_img", tokens);
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[0].get_text() == "date");
    REQUIRE(tokens[1].get_type() == TokenType::LITERAL);
    REQUIRE(tokens[1].get_text() == "_img");
}

TEST_CASE("get_tokens - literal then placeholder at end") {
    std::vector<Token> tokens;
    get_tokens("img_{seq}", tokens);
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].get_type() == TokenType::LITERAL);
    REQUIRE(tokens[0].get_text() == "img_");
    REQUIRE(tokens[1].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[1].get_text() == "seq");
}

TEST_CASE("get_tokens - adjacent placeholders") {
    std::vector<Token> tokens;
    get_tokens("{date}{time}", tokens);
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[0].get_text() == "date");
    REQUIRE(tokens[1].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[1].get_text() == "time");
}

TEST_CASE("get_tokens - adjacent placeholders with surrounding text") {
    std::vector<Token> tokens;
    get_tokens("pre{seq}{ext}post", tokens);
    REQUIRE(tokens.size() == 4);
    REQUIRE(tokens[0].get_text() == "pre");
    REQUIRE(tokens[1].get_text() == "seq");
    REQUIRE(tokens[2].get_text() == "ext");
    REQUIRE(tokens[3].get_text() == "post");
}

TEST_CASE("get_tokens - placeholder with trailing space (iso )") {
    std::vector<Token> tokens;
    get_tokens("{iso }", tokens);
    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[0].get_text() == "iso ");
}

TEST_CASE("get_tokens - single-char placeholder f") {
    std::vector<Token> tokens;
    get_tokens("{f}", tokens);
    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].get_type() == TokenType::PLACEHOLDER);
    REQUIRE(tokens[0].get_text() == "f");
}

TEST_CASE("get_tokens - literal with special characters") {
    std::vector<Token> tokens;
    get_tokens("a-b_c.123", tokens);
    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].get_type() == TokenType::LITERAL);
    REQUIRE(tokens[0].get_text() == "a-b_c.123");
}

TEST_CASE("get_tokens - placeholder is case-sensitive") {
    std::vector<Token> tokens;
    REQUIRE_THROWS(get_tokens("{Date}", tokens));
}

TEST_CASE("get_tokens - nested placeholder error ({{date}})") {
    std::vector<Token> tokens;
    REQUIRE_THROWS(get_tokens("{{date}}", tokens));
}

TEST_CASE("get_tokens - closing brace without opening throws") {
    std::vector<Token> tokens;
    REQUIRE_THROWS(get_tokens("foo}bar", tokens));
}

TEST_CASE("get_tokens - multiple interleaved tokens") {
    std::vector<Token> tokens;
    get_tokens("a{date}b{time}c", tokens);
    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0].get_text() == "a");
    REQUIRE(tokens[1].get_text() == "date");
    REQUIRE(tokens[2].get_text() == "b");
    REQUIRE(tokens[3].get_text() == "time");
    REQUIRE(tokens[4].get_text() == "c");
}

TEST_CASE("get_tokens - does not clear destination vector (appends)") {
    std::vector<Token> tokens;
    tokens.push_back(Token(TokenType::LITERAL, "start"));
    get_tokens("{seq}", tokens);
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].get_text() == "start");
    REQUIRE(tokens[1].get_text() == "seq");
}

TEST_CASE("get_tokens - long literal handling") {
    std::string longlit(1000, 'a');
    std::vector<Token> tokens;
    get_tokens(longlit + "{date}", tokens);
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].get_text().size() == 1000);
    REQUIRE(tokens[1].get_text() == "date");
}
