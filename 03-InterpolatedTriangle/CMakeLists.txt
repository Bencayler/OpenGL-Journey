# Add the executable
file(GLOB INTERPOLATEDTRIANGLE_SOURCES 
    "src/*.cpp"
    "include/*.h"
)


add_executable(InterpolatedTriangleApp ${INTERPOLATEDTRIANGLE_SOURCES})

file(GLOB SHADERS "shaders/*.vert" "shaders/*.frag")
foreach(SHADER ${SHADERS})
    configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

# Include directories
target_include_directories(InterpolatedTriangleApp PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/03-InterpolatedTriangle/include"
)



# Link libraries
target_link_libraries(InterpolatedTriangleApp PRIVATE glad "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a" opengl32)

if(WIN32)
    target_compile_definitions(InterpolatedTriangleApp  PRIVATE GLFW_INCLUDE_NONE)
endif()