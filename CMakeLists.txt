cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++11)

#set(CXX_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Capstone)

include_directories(include)

add_executable(sensor src/sensor_main.cpp src/Socket.cpp src/Network.cpp, src/sensor.cpp)
add_executable(control src/control_main.cpp src/Socket.cpp)

