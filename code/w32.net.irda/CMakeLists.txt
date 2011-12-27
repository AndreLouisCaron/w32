# w32 module.

file(GLOB ${module}_headers
  DeviceSearch.hpp
)
file(GLOB ${module}_sources
  DeviceSearch.cpp
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
