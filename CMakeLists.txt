cmake_minimum_required(VERSION 3.14)      
project(rpn_calculator)
set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
