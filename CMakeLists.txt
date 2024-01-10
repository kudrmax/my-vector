cmake_minimum_required(VERSION 3.26)
project(MySTL)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE my_src source/*.cpp)
add_executable(MySTL ${my_src})