cmake_minimum_required(VERSION 3.5.1)

project(home_control_lib_tests)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
find_package(GTest REQUIRED)

include_directories(${HOME_CONTROL_SOURCE_DIR}/home_control_lib/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(mocks)

file(GLOB ${PROJECT_NAME}_sources source/*.cpp mocks/*.h)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} home_control_lib)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
