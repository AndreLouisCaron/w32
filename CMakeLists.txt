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

# Locate custom CMake helper scripts.
set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/site
)

# In standalone builds, configure the compilation environment.
if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
  find_package(WindowsExtras)
  find_package(MSVCExtras)
  message(STATUS "Windows SDK version: '${W32_WINDOWS_VERSION}'.")
  configure_windows_sdk(${W32_WINDOWS_VERSION})
  msvc_configure_runtime()
  msvc_enable_se_handling()
endif()

# Put all libraries and executables in the build folder root.
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# Resolve our own library headers.
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/code
)

# Build the core libraries.
add_subdirectory(code)

# Export list of modules for easy linking.
set(w32_libraries ${w32_libraries} PARENT_SCOPE)

# Exclude all but the core libraries when built as a dependency.
if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})

  # Build demo projects.
  add_subdirectory(demo)

  # Locate documentation tools.
  find_package(java QUIET)
  find_package(plantuml QUIET)
  find_package(PlantUMLExtras)
  find_package(doxygen)
  find_package(DoxygenExtras)

  # Compile API documentation.
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/help/Doxyfile
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
  )
  add_api_documentation(help)

endif()
