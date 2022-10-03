cmake_minimum_required(VERSION 3.16)
project(STACK) 
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE)


include_directories(src)
add_compile_options(-std=c++17 -O2)

include_directories(tests src)
add_executable(test ./tests/test.cpp)

string (TOLOWER ${CMAKE_BUILD_TYPE} build_type)
if (build_type STREQUAL debug)
    add_compile_options(-g -fsanitize=address)
    target_link_libraries(test -fsanitize=address)
endif()
target_link_libraries(test gtest gmock pthread)