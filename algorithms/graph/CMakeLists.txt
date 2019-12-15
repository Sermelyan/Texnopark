cmake_minimum_required(VERSION 3.15)
project(graph)

set(CMAKE_CXX_STANDARD 17)

add_library(list ListGraph.cpp)
add_library(matrix MatrixGraph.cpp)
add_library(matrixrp MatrixRPGraph.cpp)
add_library(set SetGraph.cpp)
add_library(arc ArcGraph.cpp)

add_executable(test test.cpp)
target_link_libraries(test list matrix matrixrp set arc gtest)