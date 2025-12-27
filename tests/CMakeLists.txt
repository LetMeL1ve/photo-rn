cmake_minimum_required(VERSION 3.10)
include(FetchContent)

FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(catch)

add_executable(test_tokenizer
    test_tokenizer.cpp
    ../src/generator/tokenizer/tokenizer.cpp
)

target_include_directories(test_tokenizer PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_tokenizer PRIVATE Catch2::Catch2WithMain)

add_test(NAME tokenizer_tests COMMAND test_tokenizer)
