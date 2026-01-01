#pragma once
#include <string>
#include <vector>
#include "tokenizer/tokenizer.hpp"



// Main function for generating new names for images.
// ```pattern``` - Pattern for generating new name, example: ```{date}_{seq}```.
// ```result``` - Refrence to the result variable.
void generate_name(const std::string& pattern, std::string& result);

