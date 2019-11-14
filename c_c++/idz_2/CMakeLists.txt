cmake_minimum_required(VERSION 3.15)
project(idz_2)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(utils STATIC src/utils.c src/user.c src/object.c)
target_link_libraries(utils pthread)

add_library(top_single STATIC src/top_single.c src/top_utils.c)

add_library(top_multi SHARED src/top_multi.c src/top_utils.c)
target_include_directories(top_multi PUBLIC include)
target_link_libraries(top_multi pthread)


add_executable(main src/main.c)
target_link_libraries(main utils top_single dl)

add_executable(Test test/test.cpp)
target_link_libraries(Test gtest_main top_single utils dl)