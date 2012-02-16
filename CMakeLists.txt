# Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 2.6)

project(w32++)

# Locate documentation tools.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(java)
find_package(plantuml)
find_package(doxygen)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
  ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)

# Render PlantUML diagrams to PNG.
function(add_diagram target source)
  if(Java_JAVA_EXECUTABLE AND PLANTUML_JARFILE)
    set(plantuml ${Java_JAVA_EXECUTABLE} -jar ${PLANTUML_JARFILE})
    get_filename_component(output ${source} NAME_WE)
    add_custom_command(
      OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/${output}.png
      COMMAND
        ${plantuml} -o ${CMAKE_CURRENT_BINARY_DIR} -tpng ${source}
      MAIN_DEPENDENCY
        ${source}
      COMMENT
        "Rendering UML diagram '${output}'."
    )
    add_custom_target(${target}
      ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${output}.png
    )
  endif()
endfunction()

# Compile API documentation from source code.
function(add_api_documentation target)
  if(DOXYGEN_EXECUTABLE)
    add_custom_target(
      ${target}
      COMMAND
        ${DOXYGEN_EXECUTABLE}
      WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT
        "Compiling documentation."
      VERBATIM
    )
  endif()
endfunction()

# Define usual include paths, etc.
set(w32_DIR ${CMAKE_CURRENT_SOURCE_DIR})
find_package(w32 REQUIRED)

if(MSVC)
  # C and C++ runtime libraries are safe to use.
  # Don't use non-portable and inconvenient APIs
  # unless we have a reason to.
  add_definitions(
    -D_SCL_SECURE_NO_WARNINGS
    -D_CRT_SECURE_NO_WARNINGS
    -D_WIN32_WINNT=0x601
  )
  # Enable structured exception handling to support
  # translation of hardware exceptions to C++
  # exceptions.
  set(CMAKE_CXX_FLAGS
    "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996"
    CACHE STRING "Release compiler flags" FORCE)
  set(CMAKE_CXX_FLAGS_DEBUG
    "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996"
    CACHE STRING "Debug compiler flags" FORCE)
endif()

# Put all libraries and executables in the build folder root.
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# Resolve our own code in '#include <...>' directives.
include_directories(${w32_include_dir})

# Build all libraries.
add_subdirectory(code)

# When building in standalone mode, build demo projects.
if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
  add_subdirectory(demo)
endif()

# Compile inline API documentation.
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
  ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
)
add_api_documentation(help)
