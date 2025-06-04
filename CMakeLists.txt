cmake_minimum_required(VERSION 3.10)
project(OpenGL_Journals_Test VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create a shared glad library
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/Libraries/src/glad.c")
target_include_directories(glad PUBLIC 
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/Libraries/include/glm"
)

# Add subdirectories for each milestone
add_subdirectory(01-Triangle)
add_subdirectory(02-Triforce)
add_subdirectory(03-InterpolatedTriangle)
add_subdirectory(04-3DCube)
add_subdirectory(05-3DCubeTextured)
add_subdirectory(06-Camera)
add_subdirectory(07-Lighting)
add_subdirectory(08-SpecularMaps)