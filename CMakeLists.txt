cmake_minimum_required(VERSION 3.14)

project(ChernoOpenGL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB ROOT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB STB_IMAGE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/*.cpp")
file(GLOB IMGUI_IMAGE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/*.cpp")
file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

message(STATUS ${IMGUI_IMAGE_FILES})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

add_executable(ChernoOpenGL
  ${ROOT_FILES}
  ${STB_IMAGE_FILES}
  ${IMGUI_IMAGE_FILES}
  ${TEST_FILES}
)

# GLFW, OpenGL, GLEW, GLM
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(ChernoOpenGL glfw OpenGL::GL GLEW::GLEW  ${CMAKE_DL_LIBS})

# GLM
find_package(GLM REQUIRED)
target_link_libraries(ChernoOpenGL ${GLM_INCLUDE_DIRS})
