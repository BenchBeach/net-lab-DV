cmake_minimum_required(VERSION 3.17)
project(DV C)

set(CMAKE_C_STANDARD 99)

add_executable(DV main.c node0.c node1.c node2.c node3.c node.h)