#pragma once
#include <string>
#include <vector>
#include "tokenizer/tokenizer.hpp"



// Main function for generating new names for images.
// ```pattern``` - Pattern for generating new name, example: ```{date}_{seq}```.
// ```result``` - Refrence to the result variable.
// ```path``` - Path to the photo.
// ```brute``` - If true throws an error when some data are missing, else writes NONE into result.
void generate_name(const std::string&, std::string&, const std::string, bool);

