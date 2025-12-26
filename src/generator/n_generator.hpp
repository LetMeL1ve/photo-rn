#pragma once
#include <string>
#include <vector>

namespace n_generator {

// Main function for generating new names for images.
// ```pattern``` - Pattern for generating new name, example: ```{date}_{seq}```.
// ```file_info``` - All info from image EXIF for given pattern.
// ```result``` - Refrence to the result variable.
void generate_name(const std::string& pattern, const std::vector<int>/*int as buffer*/ file_info, std::string& result);
}
