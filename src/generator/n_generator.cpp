#include <string>
#include <vector>
#include <iostream>


namespace n_generator {

void get_tokens(const std::string& pattern, std::vector<std::string>& tokens) {
    bool inside = false; // True if last bracket isn't closed.
    int idx_of_opened = -1; // -1 if brackets are closed else stores position of open bracket.
    int idx_of_closed = -1;
    for (int ch = 0; ch < pattern.size(); ++ch) {
        if (pattern[ch] == '{' && !inside) {
            inside = true;
            idx_of_opened = ch;
        } else if (pattern[ch] == '}' && inside) {
            tokens.push_back(pattern.substr(idx_of_opened + 1, ch - idx_of_opened - 1));
            idx_of_opened = -1; // Setting to -1 when the brackets are closed.
            inside = false;
        }
    }
}

void generate_name(const std::string& pattern, const std::vector<int>/*int as buffer*/ file_info, 
                   std::string& result) {
    std::vector<std::string> tokens;
    get_tokens(pattern, tokens);

}

}