cmake_minimum_required(VERSION 3.10.0)
project(photo-rn VERSION 0.1.0 LANGUAGES C CXX)

# Try to find an installed CLI11 package first; otherwise fetch it as a dependency.
find_package(CLI11 REQUIRED)


add_executable(photo-rn src/main.cpp
                        src/generator/n_generator.cpp
                        src/generator/tokenizer/tokenizer.cpp
                        src/cli/cli_module.cpp)

option(BUILD_TESTS "Build tests" ON)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()


