#include <iostream>
#include "generator/n_generator.hpp"

int main() {
    std::string pattern = "{date}_{f}_{seq}.jpg";
    std::vector<int> f;
    n_generator::generate_name(pattern, f, pattern);
}
