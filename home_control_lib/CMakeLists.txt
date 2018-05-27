cmake_minimum_required (VERSION 3.5.1)
project(home_control_lib)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core)

include_directories(include)

file(GLOB ${PROJECT_NAME}_sources source/*.cpp include/*.h)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
