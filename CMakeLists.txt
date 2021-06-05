cmake_minimum_required(VERSION 3.8)
project(pico-lang)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(test)
add_subdirectory(lib/googletest)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
