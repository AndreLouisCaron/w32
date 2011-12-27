# w32 module.

file(GLOB ${module}_headers 
  __configure__.hpp
  __module__.hpp
  Editor.hpp
  Scheduler.hpp
  Status.hpp
  Task.hpp
  Tasks.hpp
  Trigger.hpp
)
file(GLOB ${module}_sources 
  __module__.cpp
  Editor.cpp
  Scheduler.cpp
  Status.cpp
  Task.cpp
  Tasks.cpp
  Trigger.cpp
)
set(${module}_libraries
  MsTask.lib
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
