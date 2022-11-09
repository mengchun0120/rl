cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")

set(TEST_COMMON_SRC
    test_common_poisson_distribution.cpp
    test_common_main.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${CMAKE_SOURCE_DIR}/unittest/common
                    ${CMAKE_SOURCE_DIR}/common)

add_executable(test_common ${TEST_COMMON_SRC})

set_property(TARGET test_common PROPERTY CXX_STANDARD 11)

target_link_libraries(test_common common)

