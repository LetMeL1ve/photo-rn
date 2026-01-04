#include <iostream>
#include "generator/generator.hpp"
#include <CLI/CLI.hpp>

int main(int argc, char* argv[]) {
    // Just for debuging, in future the will be CLI logic.
    std::string pattern = "CAMERA:{camera}___ISO:{iso}___{seq}.jpg";
    std::string result = "";
    generate_name(pattern, result, R"(D:\fotos lumix dc-s5d\prague-25-12-25\P1000177.jpg)", false, 1);
    std::cout << result;
}
