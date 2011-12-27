# w32 demonstration project.

file(GLOB ${demo-project}_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
file(GLOB ${demo-project}_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
set(${demo-project}_libraries
  w32
  w32.com
  w32.dbg
  w32.gdi
  w32.shl
  w32.shl.ext
)

add_library(${demo-project}
  SHARED
  ${${demo-project}_headers}
  ${${demo-project}_sources}
  ${CMAKE_CURRENT_SOURCE_DIR}/${demo-project}.def
)
if(${demo-project}_libraries)
  target_link_libraries(${demo-project} ${${demo-project}_libraries})
endif()
if(${demo-project}_dependencies)
  add_dependencies(${demo-project} ${${demo-project}_dependencies})
endif()
