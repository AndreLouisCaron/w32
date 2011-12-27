# w32 module.

file(GLOB ${module}_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
file(GLOB ${module}_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
set(${module}_libraries
  msi.lib
)
set(${module}_dependencies
  w32
)

add_library(${module}
  STATIC
  ${${module}_headers}
  ${${module}_sources}
)
target_link_libraries(${module} ${${module}_libraries})
add_dependencies(${module} ${${module}_dependencies})
