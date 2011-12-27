# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  check.hpp
  Connection.hpp
  ftp.hpp
  http.hpp
  IStream.hpp
  Session.hpp
  Url.hpp
)
file(GLOB ${module}_sources
  __module__.cpp
  check.cpp
  Connection.cpp
  ftp.cpp
  IStream.cpp
  Session.cpp
  Url.cpp
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
