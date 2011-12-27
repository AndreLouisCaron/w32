# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Access.hpp
  clean.hpp
  Key.hpp
  Keys.hpp
  Type.hpp
  Value.hpp
  Values.hpp
)
file(GLOB ${module}_sources
  __module__.cpp
  Access.cpp
  clean.cpp
  Key.cpp
  Keys.cpp
  Type.cpp
  Value.cpp
  Values.cpp
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
