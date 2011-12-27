# w32 module.

file(GLOB ${module}_headers 
  __configure__.hpp
  __module__.hpp
  BasicExtension.hpp
  ColumnProvider.hpp
  ContextMenu.hpp
  DropTarget.hpp
  Extension.hpp
  IconHandler.hpp
  IconOverlay.hpp
  Namespace.hpp
  PropertySheet.hpp
  ThumbnailHandler.hpp
  ThumbnailProvider.hpp
  Tooltip.hpp
)
file(GLOB ${module}_sources
  ColumnProvider.cpp
  ContextMenu.cpp
  DropTarget.cpp
  Extension.cpp
  IconHandler.cpp
  IconOverlay.cpp
  Namespace.cpp
  PropertySheet.cpp
  ThumbnailHandler.cpp
  ThumbnailProvider.cpp
  Tooltip.cpp
)
#set(${module}_libraries ...)
set(${module}_dependencies
  w32
  w32.com
  w32.shl
)

add_library(${module}
  STATIC
  ${${module}_headers}
  ${${module}_sources}
)
target_link_libraries(${module} ${${module}_libraries})
add_dependencies(${module} ${${module}_dependencies})
