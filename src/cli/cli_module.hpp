#pragma once

namespace cli {

// Main function of all CLI. Calls name generator and renames images.
// Takes ```argc``` and ```argv``` like ```main``` function.
void run(int argc, char** argv);
}