cmake_minimum_required (VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Meowcraft)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

link_directories(${CMAKE_SOURCE_DIR}/libs)

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

set(LIBS glfw3 opengl32)

add_library(STB_IMAGE "libs/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)
add_library(GLAD "libs/glad.c")
set(LIBS ${LIBS} GLAD)

# Get all source files
file(GLOB_RECURSE source "src/*.cpp" "src/*.h")
file(GLOB shaders "src/Assets/Shaders/*.glsl")
set(ALL_SOURCE ${source} ${shaders}) # Add all source files

# Add imgui
file(GLOB imgui_source "includes/imgui/*.cpp" "includes/imgui/*.h")
set(ALL_SOURCE ${ALL_SOURCE} ${imgui_source})

# Add FastNoiseLite
file(GLOB fast_noise_lite_source "includes/FastNoiseLite.h")
set(ALL_SOURCE ${ALL_SOURCE} ${fast_noise_lite_source})

add_executable(Meowcraft ${ALL_SOURCE})
include_directories(${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(Meowcraft ${LIBS})