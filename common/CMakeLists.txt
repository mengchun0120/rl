cmake_minimum_required(VERSION 3.10)

set(COMMON_SRC
    common_argument.cpp
    common_argument_parser.cpp
    common_exception.cpp
    common_json_param.cpp
    common_json_utils.cpp
    common_log.cpp
    common_math_utils.cpp
    common_out_utils.cpp
    common_parse.cpp
    common_poisson_distribution.cpp
    common_string_utils.cpp
    common_validator.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${CMAKE_SOURCE_DIR}/common)

add_library(common STATIC ${COMMON_SRC})

set_property(TARGET common PROPERTY CXX_STANDARD 11)
