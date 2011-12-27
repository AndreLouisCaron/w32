# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Columns.hpp
  Database.hpp
  Error.hpp
  ErrorRecord.hpp
  Guid.hpp
  Hash.hpp
  Object.hpp
  Product.hpp
  Products.hpp
  Record.hpp
  View.hpp
)
file(GLOB ${module}_sources 
  Columns.cpp
  Database.cpp
  Error.cpp
  ErrorRecord.cpp
  Guid.cpp
  Hash.cpp
  Object.cpp
  Product.cpp
  Products.cpp
  Record.cpp
  View.cpp
)
set(${module}_libraries
  msi.lib
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
