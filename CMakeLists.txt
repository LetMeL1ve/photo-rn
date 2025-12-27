cmake_minimum_required(VERSION 3.10.0)
project(photo-rn VERSION 0.1.0 LANGUAGES C CXX)

add_executable(photo-rn src/main.cpp
                        src/generator/n_generator.cpp
                        src/generator/tokenizer/tokenizer.cpp)

enable_testing() 
add_subdirectory(tests)

