# Add the executable
file(GLOB 3DCUBETEXTURED_SOURCES 
    "src/*.cpp"
    "include/*.h"
)


add_executable(3DCubeTextured ${3DCUBETEXTURED_SOURCES})

# Copy shaders to the build directory
file(GLOB SHADERS "shaders/*.vert" "shaders/*.frag")
foreach(SHADER ${SHADERS})
    configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

# Copy the assets folder to the build directory
file(COPY "${CMAKE_SOURCE_DIR}/05-3DCubeTextured/shaders/assets" DESTINATION "${CMAKE_BINARY_DIR}")

# Include directories
target_include_directories(3DCubeTextured PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/05-3DCubeTextured/include"
    "${CMAKE_SOURCE_DIR}/05-3DCubeTextured/shader/assets"
)



# Link libraries
target_link_libraries(3DCubeTextured PRIVATE glad "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a" opengl32)

if(WIN32)
    target_compile_definitions(3DCubeTextured PRIVATE GLFW_INCLUDE_NONE)
endif()