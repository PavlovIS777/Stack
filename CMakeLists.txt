cmake_minimum_required(VERSION 3.16)
project(STACK) 
set (CMAKE_CXX_STANDARD 17)

include_directories(src)
add_compile_options(-std=c++17 -O2)

include_directories(tests, src)
SET(TEST_FLAGS "-g -fsanitize=address")
add_definitions(${TEST_FLAGS})
SET(CMAKE_CXX_FLAGS "${TEST_FLAGS}")
add_executable(test ./tests/test.cpp)
target_link_libraries(test gtest gmock pthread)