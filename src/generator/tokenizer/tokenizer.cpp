#include "tokenizer.hpp"
#include <algorithm>

void get_tokens(const std::string& pattern, std::vector<Token>& tokens) {
    bool inside_placeholder = false;
    std::string buffer;
    for (int ch = 0; ch < pattern.size(); ++ch) {
        // Outside   {  -> Start placeholder, save buffer as literal    *
        // Outside   }  -> Error                                        *
        // Outside   ch -> Add to buffer                                   
        // Inside    {  -> Error                                        *
        // Inside    }  -> End placeholder, save buffer as placeholder  *
        // Inside    ch -> Add to buffer                                

        if (pattern[ch] == '{') {
            if (inside_placeholder) 
                throw "Invalid pattern: " + std::to_string(ch) + ": " + pattern[ch] + ". Placeholder in placeholder error.";

            inside_placeholder = true;  // Changing state.

            if (buffer.empty()) continue;  // Skipping to do not add empty token.

            // Saving token.
            tokens.push_back(
                Token(TokenType::LITERAL, buffer)
            );

            buffer.clear();
        } else if (pattern[ch] == '}') {
            if (!inside_placeholder) 
                throw "Invalid pattern: " + std::to_string(ch) + ": " + pattern[ch] + ". Closing placeholder that doesn't exist error.";

            inside_placeholder = false;  // Changing state.

            if (buffer.empty()) continue;  // Skipping to do not add empty token.

            // Checking for valid placeholder before adding it to <tokens> vector.
            if (std::find(placeholders.begin(), placeholders.end(), buffer) == placeholders.end())
                throw "Invalid pattern: " + buffer + ". Invalid placeholder error.";

            // Saving token.
            tokens.push_back(
                Token(TokenType::PLACEHOLDER, buffer)
            );

            buffer.clear();
        } else
            buffer += pattern[ch];
    }
    if (inside_placeholder)  // Checking for closed placeholder
        throw "Invalid pattern: Placeholder isn't closed error."; 
    else if (!buffer.empty()) { // Saving buffer as literal.
        tokens.push_back(
            Token(TokenType::LITERAL, buffer)
        );
    }
}