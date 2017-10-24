CMAKE_MINIMUM_REQUIRED(VERSION 2.7)

project(h4)

set(CMAKE_C_STANDARD 11)
add_executable(h4_ex4 ex4.c)
target_link_libraries(h4_ex4 pthread)

