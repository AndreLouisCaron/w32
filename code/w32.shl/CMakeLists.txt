# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Attributes.hpp
  Binding.hpp
  Browser.hpp
  Data.hpp
  Dropping.hpp
  Folder.hpp
  Item.hpp
  Link.hpp
  Listing.hpp
  Location.hpp
  Path.hpp
  Stat.hpp
  Storage.hpp
  Stream.hpp
  streambuf.hpp
  TaskbarIcon.hpp
  wallpaper.hpp
)
file(GLOB ${module}_sources
  __module__.cpp
  Attributes.cpp
  Binding.cpp
  Browser.cpp
  Data.cpp
  Dropping.cpp
  Folder.cpp
  Item.cpp
  Link.cpp
  Listing.cpp
  Location.cpp
  Path.cpp
  Stat.cpp
  Storage.cpp
  Stream.cpp
  streambuf.cpp
  TaskbarIcon.cpp
  wallpaper.cpp
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
