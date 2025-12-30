#include "CLI/CLI.hpp"
#include "cli_module.hpp"
#include <iostream>

namespace cli {

void run(int argc, char** argv) {
    // photo-rn <path> <pattern>

    CLI::App app {"", "Photo Renamer"};

    std::string working_dir = "";
    std::string pattern = "";

    app.add_option("dir", working_dir, "Direction that contains images that should be renamed.")->required();

    app.add_option("pattern", pattern, "Pattern for renaming images.")->required();

    try { 
        (app).parse(argc, argv);
    } catch(const CLI::ParseError &e) { 
        throw "Invalid input.";
    }
    std::cout << working_dir << " " << pattern;
}
}