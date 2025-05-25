cmake_minimum_required(VERSION 3.10)
project(OpenGL_Journals_Test VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Optionally, keep a main project
add_executable(hello_window src/main.cpp src/glad.c)
target_include_directories(hello_window PRIVATE
    "include"
    "${CMAKE_SOURCE_DIR}/Libraries/include"
)
target_link_libraries(hello_window PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a"
    opengl32
)
if(WIN32)
    target_compile_definitions(hello_window PRIVATE GLFW_INCLUDE_NONE)
endif()

# Add subdirectories for each milestone
add_subdirectory(Triangle)
add_subdirectory(Triforce)