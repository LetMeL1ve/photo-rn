#include <iostream>
#include "generator/n_generator.hpp"

int main() {
    std::string pattern = "{abc}_{seq}";
    std::vector<int> f;
    n_generator::generate_name(pattern, f, pattern);
}
