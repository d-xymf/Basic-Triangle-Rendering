cmake_minimum_required(VERSION 3.12)
project(Basic-Triangle-Rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

add_library(glad src/glad.c)

set(GLFW_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/glfw3.lib")

add_executable(Basic-Triangle-Rendering src/main.cpp)
target_link_libraries(Basic-Triangle-Rendering glad ${GLFW_LIB_PATH})