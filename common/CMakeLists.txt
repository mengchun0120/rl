cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(COMMON_SRC
    common_poisson_distribution.cpp
    common_math_utils.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${CMAKE_SOURCE_DIR}/common)

add_library(common STATIC ${COMMON_SRC})

set_property(TARGET common PROPERTY CXX_STANDARD 11)
