# win32++: More C++ wrappers for the Win32 API.

cmake_minimum_required(VERSION 2.6)

project(w32++)

# Define usual include paths, etc.
find_package(w32 REQUIRED)

if(MSVC)
  # C and C++ runtime libraries are safe to use.
  # Don't use non-portable and inconvenient APIs
  # unless we have a reason to.
  add_definitions(
    -D_SCL_SECURE_NO_WARNINGS
    -D_CRT_SECURE_NO_WARNINGS
  )
  # Enable structured exception handling to support
  # translation of hardware exceptions to C++
  # exceptions.
  set(CMAKE_CXX_FLAGS
    "/DWIN32 /D_WINDOWS /EHsc /wd4355"
    CACHE STRING "Release compiler flags" FORCE)
  set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} /WX /wd4355"
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
