cmake_minimum_required(VERSION 3.15)
project(idz_2)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(utils STATIC src/utils.c src/user.c src/object.c)
target_link_libraries(utils pthread)

add_executable(main src/main.c)
target_link_libraries(main utils)