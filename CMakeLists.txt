cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CMakePrintHelpers)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Capstone)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(SRC_DIR src)
file(GLOB INC_FILES include/*)
set(SENSOR_SRC_FILES src/sensor/sensor_main.cpp src/network/Socket.cpp src/network/Network.cpp src/sensor/Sensor.cpp src/message/Message.cpp)
set(CONTROL_SRC_FILES src/control_unit/control_main.cpp src/network/Network.cpp src/network/Socket.cpp src/control_unit/InputController.cpp src/display/Display.cpp src/control_unit/Controller.cpp src/message/Message.cpp)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${INC_FILES})
cmake_print_variables(${SENSOR_SRC_FILES})

#add_executable(sensor src/sensor/sensor_main.cpp src/network/Socket.cpp src/network/Network.cpp src/sensor/Sensor.cpp)
add_executable(sensor ${SENSOR_SRC_FILES})
add_executable(control ${CONTROL_SRC_FILES})

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(control ${SDL2_LIBRARIES})

