# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Allocator.hpp
  cast.hpp
  Context.hpp
  Error.hpp
  Factory.hpp
  Guid.hpp
  instantiate.hpp
  Library.hpp
  Model.hpp
  Object.hpp
  Ptr.hpp
  Result.hpp
  String.hpp
  Threading.hpp
  Wrapper.hpp
)
file(GLOB ${module}_sources
  __module__.cpp
  Allocator.cpp
  Context.cpp
  Error.cpp
  Factory.cpp
  Guid.cpp
  Library.cpp
  Model.cpp
  Object.cpp
  Result.cpp
  Threading.cpp
)
set(${module}_libraries
  kernel32.lib
)

add_library(${module}
  STATIC
  ${${module}_headers}
  ${${module}_sources}
)
if(${module}_libraries)
  target_link_libraries(${module} ${${module}_libraries})
endif()
if(${module}_dependencies)
  add_dependencies(${module} ${${module}_dependencies})
endif()
