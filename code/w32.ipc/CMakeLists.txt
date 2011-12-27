# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Job.hpp
  Modules.hpp
  Process.hpp
  Processes.hpp
  Startup.hpp
  Threads.hpp
)
file(GLOB ${module}_sources
  __module__.cpp
  Job.cpp
  Modules.cpp
  Process.cpp
  Processes.cpp
  Startup.cpp
  Threads.cpp
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
