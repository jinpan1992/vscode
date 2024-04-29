# CMakeLists.txt  
cmake_minimum_required(VERSION 3.10)  
  
project(MultithreadedApp C)  

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wall")
#设置为调试模式
set(CMAKE_BUILD_TYPE Debug)
  
# 添加pthread库  
find_package(Threads REQUIRED)  

#指定编译器
set(CMAKE_C_COMPILER "/usr/bin/gcc")
  
# 添加源文件  
add_executable(hello hello.c)  
  
# 链接pthread库  
target_link_libraries(hello Threads::Threads)
 
