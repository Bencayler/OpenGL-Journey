add_executable(TriangleApp src/main.cpp ../src/glad.c)

target_include_directories(TriangleApp PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/Triangle/include"
)

target_link_libraries(TriangleApp PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a"
    opengl32
)

if(WIN32)
    target_compile_definitions(TriangleApp PRIVATE GLFW_INCLUDE_NONE)
endif()