cmake_minimum_required(VERSION 3.11)

project(TurboVis VERSION 1.1)

set(CMAKE_CXX_STANDARD 14)

add_executable(TurboVis_opengl_glfw glfw_opengl3/main.cpp)

target_sources(TurboVis_opengl_glfw PUBLIC
	${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
	${CMAKE_SOURCE_DIR}/imgui/imgui_demo.cpp
	${CMAKE_SOURCE_DIR}/imgui/imgui_impl_glfw.cpp
	${CMAKE_SOURCE_DIR}/imgui/imgui_impl_opengl3.cpp
	${CMAKE_SOURCE_DIR}/imgui/imgui_impl_win32.cpp
	${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp
	${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp

	${CMAKE_SOURCE_DIR}/implot/implot.cpp
	${CMAKE_SOURCE_DIR}/implot/implot_demo.cpp
	${CMAKE_SOURCE_DIR}/implot/implot_items.cpp

	${CMAKE_SOURCE_DIR}/turbovisLib/AxialCompressor.cpp
	${CMAKE_SOURCE_DIR}/turbovisLib/AxialTurbine.cpp
	${CMAKE_SOURCE_DIR}/turbovisLib/Stage.cpp
	${CMAKE_SOURCE_DIR}/turbovisLib/StageContext.cpp
	${CMAKE_SOURCE_DIR}/turbovisLib/TurboVis.cpp
	${CMAKE_SOURCE_DIR}/turbovisLib/Vec.cpp
)

target_include_directories(TurboVis_opengl_glfw PUBLIC
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/GLFW/include
	${CMAKE_SOURCE_DIR}/imgui
	${CMAKE_SOURCE_DIR}/implot
	${CMAKE_SOURCE_DIR}/turbovisLib
	${CMAKE_SOURCE_DIR}/glfw_opengl3
	
)

target_link_libraries(TurboVis_opengl_glfw LINK_PUBLIC
	${CMAKE_SOURCE_DIR}/GLFW/lib-vc2010-32/glfw3.lib)