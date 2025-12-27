#include <iostream>
#include "generator/n_generator.hpp"

int main() {
    std::string pattern = "IMG_{date}_{seq}_IMG";
    std::vector<int> f;
    n_generator::generate_name(pattern, f, pattern);
}
