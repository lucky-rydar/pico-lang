set(BINARY gTest)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

# for gcov
SET(CMAKE_CXX_FLAGS  "-g -O0 -fprofile-arcs -ftest-coverage")

set(SOURCES ${TEST_SOURCES})

set(SRC_DIR "../src")
set(GTEST_LIB_DIR "../lib/googletest/googletest/include")

include_directories(${GTEST_LIB_DIR} ${SRC_DIR})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

set(UNIT_TEST ${BINARY})

add_custom_command(
     TARGET ${UNIT_TEST}
     COMMENT "Running tests"
     POST_BUILD 
     COMMAND ${UNIT_TEST}
)

set(GCOVR_SCRIPT sh ../../scripts/gcovr.sh)

add_custom_command(
     TARGET ${UNIT_TEST}
     COMMENT "Gcovr running..."
     POST_BUILD
     COMMAND ${GCOVR_SCRIPT}
)