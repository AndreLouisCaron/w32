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
  w32.ipc
  w32.mt
)

add_executable(${demo-project}
  ${${demo-project}_headers}
  ${${demo-project}_sources}
)
if(${demo-project}_libraries)
  target_link_libraries(${demo-project} ${${demo-project}_libraries})
endif()
if(${demo-project}_dependencies)
  add_dependencies(${demo-project} ${${demo-project}_dependencies})
endif()
