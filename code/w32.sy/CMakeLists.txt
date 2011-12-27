# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  AccessControlList.hpp
  Attributes.hpp
  Descriptor.hpp
  Identifier.hpp
  Impersonation.hpp
  ImpersonationLevel.hpp
  Token.hpp
)
file(GLOB ${module}_sources
  __module__.cpp
  AccessControlList.cpp
  Attributes.cpp
  Descriptor.cpp
  Identifier.cpp
  Impersonation.cpp
  ImpersonationLevel.cpp
  Token.cpp
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
