# w32 module.

file(GLOB ${module}_headers A
  __configure__.hpp
  __module__.hpp
  ttributes.hpp
  ContentHandler.hpp
  DtdHandler.hpp
  ErrorHandler.hpp
  LexicalHandler.hpp
  Locator.hpp
  Reader.hpp
)
file(GLOB ${module}_sources
  Attributes.cpp
  Locator.cpp
)
#set(${module}_libraries ...)
set(${module}_dependencies
  w32
  w32.com
)

add_library(${module}
  STATIC
  ${${module}_headers}
  ${${module}_sources}
)
target_link_libraries(${module} ${${module}_libraries})
add_dependencies(${module} ${${module}_dependencies})
