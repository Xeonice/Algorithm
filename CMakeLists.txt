cmake_minimum_required(VERSION 3.9)
project(Algorithm)

set(CMAKE_CXX_STANDARD 11)

include_directories("./")
add_executable(select-sort sort/select-sort.cpp)
add_executable(insert-sort sort/insert-sort.cpp)
add_executable(4.1 Data-structure/4.1.cpp)
add_executable(4.2 Data-structure/4.2.c)
add_executable(4.3 Data-structure/4.3.c)
add_executable(4.7 Data-structure/4.7.c)
add_executable(5.1 Data-structure/5.1.c)
add_executable(5.2 Data-structure/5.2.cpp)
add_executable(5.3 Data-structure/5.3.cpp)
add_executable(6.1.1 Data-structure/6.1.1.c)
add_executable(6.1.2 Data-structure/6.1.2.c)

add_executable(test3 test3/test3.cpp)

