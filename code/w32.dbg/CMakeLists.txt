# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Event.hpp
  Log.hpp
  StructuredException.hpp
)
file(GLOB ${module}_sources
  Event.cpp
  Log.cpp
  StructuredException.cpp
)
#set(${module}_libraries ...)
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
