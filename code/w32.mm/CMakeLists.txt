# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Aligned.hpp
  Allocator.hpp
  Global.hpp
  Heap.hpp
  Local.hpp
  Mapping.hpp
  Shared.hpp
  Virtual.hpp
)
file(GLOB ${module}_sources
  Aligned.cpp
  Global.cpp
  Heap.cpp
  Local.cpp
  Mapping.cpp
  Shared.cpp
  Virtual.cpp
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
