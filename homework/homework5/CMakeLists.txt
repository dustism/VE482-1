CMAKE_MINIMUM_REQUIRED(VERSION 2.7)

project(h5)

set(CMAKE_CXX_STANDARD 11)
add_executable(h5_ex4 ex4.cpp)
target_link_libraries(h5_ex4 pthread)

