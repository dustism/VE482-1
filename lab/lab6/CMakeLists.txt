cmake_minimum_required(VERSION 3.8)
project(xor_linked_list)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c dlist.c dlist.h list.c list.h)
add_executable(xor_linked_list ${SOURCE_FILES})