# Add the executable
file(GLOB TRIANGLE_SOURCES "src/*.cpp")
add_executable(TriangleApp ${TRIANGLE_SOURCES})

# Include directories
target_include_directories(TriangleApp PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/01-Triangle/include"
)

# Link libraries
target_link_libraries(TriangleApp PRIVATE glad "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a" opengl32)

if(WIN32)
    target_compile_definitions(TriangleApp PRIVATE GLFW_INCLUDE_NONE)
endif()