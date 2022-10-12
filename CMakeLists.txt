cmake_minimum_required(VERSION 3.16)
project(STACK) 
set(CMAKE_CXX_STANDARD 17)
file(MAKE_DIRECTORY build)

include_directories(inc src tests)
add_compile_options(-std=c++17 -O2)


#tests
add_executable(test ${CMAKE_SOURCE_DIR}/tests/test.cpp ${CMAKE_SOURCE_DIR}/src/stack.cpp)
string (TOLOWER DCMAKE_BUILD_TYPE build_type)
if (build_type STREQUAL debug)
    add_compile_options(-g -fsanitize=address)
    target_link_libraries(test -fsanitize=address)
endif()
target_link_libraries(test gtest gmock pthread)


#clang-tidy
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
	add_custom_target(
	clang-tidy
	COMMAND clang-tidy ${CMAKE_SOURCE_DIR}/src/stack.cpp -- -std=c++17 -O2 -I ${CMAKE_SOURCE_DIR}/inc
	)
endif()


#clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    clang-format
    COMMAND find ../ -iname *.h -o -iname *.c -o -iname *.cpp -o -iname *.hpp | xargs clang-format -style=file -i -fallback-style=none
    )
endif()