# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Buffer.hpp
  Context.hpp
  DatagramSocket.hpp
  Event.hpp
  Family.hpp
  Host.hpp
  hostname.hpp
  integers.hpp
  irda.hpp
  select.hpp
  Set.hpp
  Socket.hpp
  sockstream.hpp
  streambuf.hpp
  StreamSocket.hpp
  Timespan.hpp
)
file(GLOB ${module}_sources
  Buffer.cpp
  Context.cpp
  DatagramSocket.cpp
  Event.cpp
  Family.cpp
  Host.cpp
  hostname.cpp
  integers.cpp
  select.cpp
  Set.cpp
  Socket.cpp
  sockstream.cpp
  streambuf.cpp
  StreamSocket.cpp
  Timespan.cpp
)
set(${module}_libraries
  ws2_32.lib
)
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
