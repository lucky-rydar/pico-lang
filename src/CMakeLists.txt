set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB SRC_FILES "*.cpp")
file(GLOB HEADER_FILES "*.h")

add_executable(${BINARY} ${SRC_FILES} ${HEADER_FILES})

add_library(${BINARY}_lib STATIC ${SRC_FILES} ${HEADER_FILES})