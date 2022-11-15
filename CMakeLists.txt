cmake_minimum_required(VERSION 3.10)

project(rl CXX)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

add_subdirectory(common)
add_subdirectory(carrental1)
add_subdirectory(unittest)
