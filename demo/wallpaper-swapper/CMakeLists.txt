# w32 demonstration project.

file(GLOB ${demo-project}_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
file(GLOB ${demo-project}_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
set(${demo-project}_libraries
  w32
  w32.dbg
  w32.fs
  w32.gdi
  w32.mt
  w32.rgs
  w32.shl
)
set(${demo-project}_dependencies
  w32
  w32.dbg
  w32.fs
  w32.gdi
  w32.mt
  w32.rgs
  w32.shl
)

add_executable(${demo-project}
  WIN32
  ${${demo-project}_headers}
  ${${demo-project}_sources}
)
if(${demo-project}_libraries)
  target_link_libraries(${demo-project} ${${demo-project}_libraries})
endif()
if(${demo-project}_dependencies)
  add_dependencies(${demo-project} ${${demo-project}_dependencies})
endif()
