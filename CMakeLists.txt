cmake_minimum_required(VERSION 3.20)

project(NovaSearch VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NovaSearch
    app/main.cpp
    src/NovaSearch.cpp
    src/tokenizer.cpp
)

target_include_directories(NovaSearch PRIVATE include)

# Tokenizer tests
add_executable(test_tokenizer
    tests/test_tokenizer.cpp
    src/tokenizer.cpp
)

target_include_directories(test_tokenizer PRIVATE include)