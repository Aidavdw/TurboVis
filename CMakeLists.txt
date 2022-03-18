cmake_minimum_required(VERSION 3.10)

project(TurboVis VERSION 1.1)

set(CMAKE_CXX_STANDARD 14)


add_executable(TurboVis_opengl_glfw glfw_opengl3/main.cpp)