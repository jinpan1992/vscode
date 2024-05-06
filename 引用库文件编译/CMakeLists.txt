cmake_minimum_required(VERSION 3.0)

project(camke_lib)

set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/main.c)

include_directories(${PROJECT_SOURCE_DIR}/testFunc/inc)

find_library(TESTFUNC_LIB testFunc HINTS ${PROJECT_SOURCE_DIR}/testFunc/lib)

add_executable(main ${SRC_LIST})

target_link_libraries(main ${TESTFUNC_LIB})