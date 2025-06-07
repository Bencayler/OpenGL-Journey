# Add the executable
file(GLOB MESHCLASS_SOURCES 
    "src/*.cpp"
    "include/*.h"
)


add_executable(MeshClass ${MESHCLASS_SOURCES})

# Copy shaders to the build directory
file(GLOB SHADERS "shaders/*.vert" "shaders/*.frag")
foreach(SHADER ${SHADERS})
    configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

# Copy assets to the build directory
# In the future there may be a more elegant way to do this with specific
# commands, but as of now there is very little in the way of assets in here
# so the single wilcard does fine.
file(GLOB ASSETS "shaders/assets/*")
foreach(ASSET ${ASSETS})
    configure_file(${ASSET} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

# Copy the assets folder to the build directory
file(COPY "${CMAKE_SOURCE_DIR}/10-MeshClass/shaders/assets" DESTINATION "${CMAKE_BINARY_DIR}")

# Include directories
target_include_directories(MeshClass PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/10-MeshClass/include"
    "${CMAKE_SOURCE_DIR}/10-MeshClass/shader/assets"
)



# Link libraries
target_link_libraries(MeshClass PRIVATE glad "${CMAKE_SOURCE_DIR}/Libraries/lib/libglfw3.a" opengl32)

if(WIN32)
    target_compile_definitions(MeshClass PRIVATE GLFW_INCLUDE_NONE)
endif()