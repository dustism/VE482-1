cmake_minimum_required(VERSION 3.8)
project(l6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c dlist.c dlist.h list.c list.h)
add_executable(l6 ${SOURCE_FILES})