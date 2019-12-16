cmake_minimum_required(VERSION 3.15)
project(dz_3_2)

set(CMAKE_CXX_STANDARD 17)

add_library(list ListGraph.cpp)

add_executable(main main.cpp)
target_link_libraries(main list)