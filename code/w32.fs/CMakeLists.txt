# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  absolute.hpp
  Attributes.hpp
  Changes.hpp
  copy.hpp
  drives.hpp
  File.hpp
  Folder.hpp
  hardlink.hpp
  junction.hpp
  move.hpp
  Search.hpp
  symlink.hpp
  Time.hpp
  unlink.hpp
)
file(GLOB ${module}_sources 
  absolute.cpp
  Attributes.cpp
  Changes.cpp
  copy.cpp
  drives.cpp
  File.cpp
  Folder.cpp
  hardlink.cpp
  junction.cpp
  move.cpp
  Search.cpp
  symlink.cpp
  Time.cpp
  unlink.cpp
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
