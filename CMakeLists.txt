# win32++: More C++ wrappers for the Win32 API.

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
