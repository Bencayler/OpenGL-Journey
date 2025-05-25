add_executable(TriforceApp src/main.cpp ../src/glad.c)

target_include_directories(TriforceApp PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/Triforce/include"
)

target_link_libraries(TriforceApp PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a"
    opengl32
)

if(WIN32)
    target_compile_definitions(TriforceApp PRIVATE GLFW_INCLUDE_NONE)
endif()