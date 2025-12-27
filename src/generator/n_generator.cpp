#include "n_generator.hpp"

namespace n_generator {

void generate_name(const std::string& pattern, const std::vector<int>/*int as buffer*/ file_info, 
                   std::string& result) {
    std::vector<Token> tokens;
    get_tokens(pattern, tokens);
    
}

}