cmake_minimum_required(VERSION 3.9)
project(Algorithm)

set(CMAKE_CXX_STANDARD 11)

include_directories("./")
add_executable(test1 sort/test.cpp)
add_executable(test2 test2/test2.cpp)
add_executable(test3 test3/test3.cpp)

