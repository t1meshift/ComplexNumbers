cmake_minimum_required(VERSION 3.12)
project(ComplexNum)

set(CMAKE_CXX_STANDARD 14)
add_compile_options("--coverage")
link_libraries("--coverage")

find_package(Catch2 REQUIRED)
add_executable(ComplexNum main.cpp complex.cpp complex.h)
target_link_libraries(ComplexNum Catch2::Catch2)