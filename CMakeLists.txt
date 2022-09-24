cmake_minimum_required(VERSION 3.22)

project(GLSandbox VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_SHARED_LIBS "build shared libs" OFF)

add_executable(GLSandbox main.cpp glad.c)

# find_package(glfw3 3 REQUIRED)
# find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

message("OpenGL include dir: ${OPENGL_INCLUDE_DIR}")
message("glfw include dir: ${GLFW3_INCLUDE_DIR}")



# target_link_libraries(GLSandbox OpenGL::GL ${GLFW3_LIBRARY})

target_include_directories(GLSandbox PUBLIC 
    ${OPENGL_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}"
    # $<INSTALL_INTERFACE:include>
)

target_link_libraries(GLSandbox OpenGL::GL glfw)
# install(TARGETS GLSandbox DESTINATION bin)


