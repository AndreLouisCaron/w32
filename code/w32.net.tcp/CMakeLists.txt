# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  Listener.hpp
  Stream.hpp
)
file(GLOB ${module}_sources
  Listener.cpp
  Stream.cpp
)
#set(${module}_libraries ...)
set(${module}_dependencies
  w32
  w32.net
)

add_library(${module}
  STATIC
  ${${module}_headers}
  ${${module}_sources}
)
target_link_libraries(${module} ${${module}_libraries})
add_dependencies(${module} ${${module}_dependencies})
