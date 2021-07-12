cmake_minimum_required(VERSION 3.8)
project(pico-lang)

set(CMAKE_CXX_STANDARD 17)

# for gcov
SET(CMAKE_CXX_FLAGS  "-g -O0 -fprofile-arcs -ftest-coverage")

include_directories(src)

add_subdirectory(test)
add_subdirectory(lib/googletest)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
