cmake_minimum_required(VERSION 3.5.1)

project(home_control_app)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SYSROOT "/home/oleksii/raspi/sysroot")

find_package(Qt5Core REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/home_control_lib/include)
include_directories(include)

file(GLOB ${PROJECT_NAME}_sources source/*.cpp include/*.h)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

add_subdirectory (dht_sensor)
include_directories(${HOME_CONTROL_SOURCE_DIR}/home_control_app/dht_sensor/dht_sensor_lib/include)
include_directories(${HOME_CONTROL_SOURCE_DIR}/home_control_app/dht_sensor/raspberry_pi_lib/include)

target_link_libraries(${PROJECT_NAME} dht_sensor_lib)
target_link_libraries(${PROJECT_NAME} raspberry_pi_lib)
target_link_libraries(${PROJECT_NAME} home_control_lib)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
