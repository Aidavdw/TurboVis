cmake_minimum_required(VERSION 3.11)

project(TurboVis VERSION 1.1)

set(CMAKE_CXX_STANDARD 14)

# Double check if this works also on linux
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SRC_IMGUI imgui/src/*.cpp)
file(GLOB_RECURSE SRC_IMPLOT implot/src/*.cpp)
file(GLOB_RECURSE SRC_TURBOVISLIB turbovisLib/src/*.cpp)

# Building GLFW
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw-3.3.6)

add_executable(TurboVis_opengl_glfw
	glfw_opengl3/main.cpp
	${SRC_IMGUI}
	${SRC_IMPLOT}
	${SRC_TURBOVISLIB}
)

target_include_directories(TurboVis_opengl_glfw PUBLIC
	${CMAKE_SOURCE_DIR}/imgui/include
	${CMAKE_SOURCE_DIR}/implot/include
	${CMAKE_SOURCE_DIR}/turbovisLib/include
	${CMAKE_SOURCE_DIR}/glfw-3.3.6/include
)

target_link_libraries(TurboVis_opengl_glfw LINK_PUBLIC
	${OPENGL_gl_LIBRARY}
	glfw
	${GLFW_LIBRARIES}
)