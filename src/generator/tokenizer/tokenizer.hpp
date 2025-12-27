#pragma once 
#include "token.hpp"
#include <vector>
#include <array>

inline const std::array<std::string, 9> placeholders {
    "date",
    "time",
    "camera",
    "lens",
    "iso ",
    "f",
    "seq",
    "orig",
    "ext"
};

void get_tokens(const std::string& pattern, std::vector<Token>& tokens);