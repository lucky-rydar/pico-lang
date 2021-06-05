cmake_minimum_required(VERSION 3.8)
project(pico-lang)

set(CMAKE_CXX_STANDARD 17)

include_directories("include" "src")

file(GLOB SRC_FILES "src/*.cpp")
file(GLOB HEADER_FILES "include/*.h")

add_executable(pico-lang ${SRC_FILES} ${HEADER_FILES})