# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Blob.hpp
  Hash.hpp
  Key.hpp
  Provider.hpp
)
file(GLOB ${module}_sources
  Blob.cpp
  Hash.cpp
  Key.cpp
  Provider.cpp
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
