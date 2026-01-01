#include <iostream>
#include "generator/generator.hpp"
#include <CLI/CLI.hpp>

int main(int argc, char* argv[]) {
    // Just for debuging, in future the will be CLI logic.
    std::string pattern;
    std::string result = "";
    generate_name(pattern, result);
    
}
