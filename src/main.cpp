#include <iostream>
#include "generator/n_generator.hpp"
#include "cli/cli_module.hpp"

int main(int argc, char** argv) {
    std::cout << cli::run(argc, argv);
}
