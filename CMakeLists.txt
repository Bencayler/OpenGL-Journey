cmake_minimum_required(VERSION 3.10)
project(OpenGL_Journals_Test VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create a shared glad library
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/Libraries/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/Libraries/include")

# Remove or comment out the hello_window executable block
# add_executable(hello_window src/main.cpp)
# target_include_directories(hello_window PRIVATE
#     "include"
#     "${CMAKE_SOURCE_DIR}/Libraries/include"
# )
# target_link_libraries(hello_window PRIVATE glad "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a" opengl32)
# if(WIN32)
#     target_compile_definitions(hello_window PRIVATE GLFW_INCLUDE_NONE)
# endif()

# Add subdirectories for each milestone
add_subdirectory(01-Triangle)
add_subdirectory(02-Triforce)