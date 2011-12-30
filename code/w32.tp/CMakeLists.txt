# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Cleanup.hpp
  Hints.hpp
  Pool.hpp
  Queue.hpp
  Timer.hpp
  Transfer.hpp
  Wait.hpp
  Work.hpp
)
file(GLOB ${module}_sources
  Cleanup.cpp
  Hints.cpp
  Pool.cpp
  Queue.cpp
  Timer.cpp
  Transfer.cpp
  Wait.cpp
  Work.cpp
)
#set(${module}_libraries ...)
set(${module}_dependencies
  w32
  w32.mt
)

add_library(${module}
  STATIC
  ${${module}_headers}
  ${${module}_sources}
)
target_link_libraries(${module} ${${module}_libraries})
add_dependencies(${module} ${${module}_dependencies})
