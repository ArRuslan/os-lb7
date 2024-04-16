cmake_minimum_required(VERSION 3.28)
project(os_lb7)

set(CMAKE_CXX_STANDARD 17)

add_executable(os_lb7 main.cpp procinfo.hpp)
add_executable(lb7t2p1 task2prog1.cpp procinfo.hpp)
add_executable(lb7t2p2 task2prog2.cpp procinfo.hpp)

add_dependencies(os_lb7 lb7t2p1 lb7t2p2)
