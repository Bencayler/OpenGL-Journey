# Add the executable
file(GLOB TRIFORCE_SOURCES 
    "src/*.cpp"
    "include/*.h"
)


add_executable(TriforceApp ${TRIFORCE_SOURCES})

file(GLOB SHADERS "shaders/*.vert" "shaders/*.frag")
foreach(SHADER ${SHADERS})
    configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

# Include directories
target_include_directories(TriforceApp PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/02-Triforce/include"
)



# Link libraries
target_link_libraries(TriforceApp PRIVATE glad "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a" opengl32)

if(WIN32)
    target_compile_definitions(TriforceApp PRIVATE GLFW_INCLUDE_NONE)
endif()