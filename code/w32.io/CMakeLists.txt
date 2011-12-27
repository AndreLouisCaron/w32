# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  AnonymousPipe.hpp
  Channel.hpp
  CompletionPort.hpp
  ConsoleInput.hpp
  ConsoleOutput.hpp
  InputFile.hpp
  InputStream.hpp
  NamedPipe.hpp
  Null.hpp
  OutputFile.hpp
  OutputStream.hpp
  SerialPort.hpp
  StandardError.hpp
  StandardInput.hpp
  StandardOutput.hpp
  Stream.hpp
  streambuf.hpp
  Transfer.hpp
)
file(GLOB ${module}_sources
  __module__.cpp
  AnonymousPipe.cpp
  Channel.cpp
  CompletionPort.cpp
  ConsoleInput.cpp
  ConsoleOutput.cpp
  InputFile.cpp
  InputStream.cpp
  NamedPipe.cpp
  Null.cpp
  OutputFile.cpp
  OutputStream.cpp
  SerialPort.cpp
  StandardError.cpp
  StandardInput.cpp
  StandardOutput.cpp
  Stream.cpp
  streambuf.cpp
  Transfer.cpp
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
