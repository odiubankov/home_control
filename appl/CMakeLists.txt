cmake_minimum_required (VERSION 3.5.1)
project (home_control_app)

set (HOME_CONTROL_SOURCE_DIR ${CMAKE_SOURCE_DIR})

add_subdirectory (home_control_lib)
add_subdirectory (home_control_app)
