cmake_minimum_required (VERSION 3.5.1)
project(home_control_lib)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB ${PROJECT_NAME}_sources source/*.cpp include/*.h)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources})