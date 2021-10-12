cmake_minimum_required(VERSION 3.14)

project(ChernoOpenGL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(ChernoOpenGL
  main.cpp
  renderer.h renderer.cpp
  vertexbuffer.h vertexbuffer.cpp
  indexbuffer.h indexbuffer.cpp
  vertexarray.h vertexarray.cpp
  vertexbufferlayout.h
  shader.h shader.cpp
  texture.h texture.cpp
  vendor/stb_image/stb_image.h vendor/stb_image/stb_image.cpp
)

# GLFW, OpenGL, GLEW, GLM
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(ChernoOpenGL glfw OpenGL::GL GLEW::GLEW)

# GLM
find_package(GLM REQUIRED)
target_link_libraries(ChernoOpenGL ${GLM_INCLUDE_DIRS})
