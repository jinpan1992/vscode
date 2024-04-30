#多文件编译
cmake_minimum_required(VERSION 3.0)

project(SWAP)

set(CMAKE_C_COMPILER "/usr/bin/gcc")

include_directories(include)

add_executable(main_cmake main.c src/swap.c)
