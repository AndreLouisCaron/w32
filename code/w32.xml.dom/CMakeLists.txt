# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Attribute.hpp
  Attributes.hpp
  CData.hpp
  Comment.hpp
  Document.hpp
  Element.hpp
  Error.hpp
  Instruction.hpp
  List.hpp
  Node.hpp
  Text.hpp
  Visitor.hpp
  walk.hpp
)
file(GLOB ${module}_sources
  Attribute.cpp
  Attributes.cpp
  CData.cpp
  Comment.cpp
  Document.cpp
  Element.cpp
  Error.cpp
  Instruction.cpp
  List.cpp
  Node.cpp
  Text.cpp
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
