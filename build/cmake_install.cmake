# Install script for directory: C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/OpenGL_Journals_Test")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/MinGW/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/01-Triangle/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/02-Triforce/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/03-InterpolatedTriangle/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/04-3DCube/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/05-3DCubeTextured/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/06-Camera/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/07-Lighting/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/08-SpecularMaps/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/09-TypesOfLight/cmake_install.cmake")
  include("C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/10-MeshClass/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/THEJANKMACHINE/Documents/VSCode/OpenGL_Journals_Test/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
