cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")

set(CARRENTAL1_SRC
    carrental1_main.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${CMAKE_SOURCE_DIR}/carrental1)

add_executable(carrental1 ${CARRENTAL1_SRC})

set_property(TARGET carrental1 PROPERTY CXX_STANDARD 11)

