# w32 module.

file(GLOB ${module}_headers 
  __configure__.hpp
  __module__.hpp
  Action.hpp
  Actions.hpp
  Definition.hpp
  Execution.hpp
  Executions.hpp
  Folder.hpp
  Folders.hpp
  Handler.hpp
  Principal.hpp
  Registration.hpp
  Registrations.hpp
  Service.hpp
  State.hpp
)
file(GLOB ${module}_sources 
  __module__.cpp
  Action.cpp
  Actions.cpp
  Definition.cpp
  Execution.cpp
  Executions.cpp
  Folder.cpp
  Folders.cpp
  Handler.cpp
  Principal.cpp
  Registration.cpp
  Registrations.cpp
  Service.cpp
  State.cpp
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
