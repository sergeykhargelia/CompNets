cmake_minimum_required(VERSION 3.22)
project(vector_distance_routing CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -Werror -pedantic")

add_executable(dv main.cpp)
add_executable(dv_test test.cpp)