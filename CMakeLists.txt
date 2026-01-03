cmake_minimum_required(VERSION 3.10.0)
project(photo-rn VERSION 0.1.0 LANGUAGES C CXX)

# Used for CLI interface
find_package(CLI11 REQUIRED)

find_package(exiv2 REQUIRED)


add_executable(photo-rn src/main.cpp
                        src/generator/generator.cpp
                        src/generator/tokenizer/tokenizer.cpp
                        src/reader/reader.cpp
                        src/fileinfo.cpp)

target_link_libraries(photo-rn PUBLIC exiv2)

option(BUILD_TESTS "Build tests" ON)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()


