# w32 module.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  atomic.hpp
  AutoResetEvent.hpp
  Cleanup.hpp
  ConditionVariable.hpp
  CriticalSection.hpp
  List.hpp
  ManualResetEvent.hpp
  Mutex.hpp
  Pool.hpp
  Queue.hpp
  ReadWriteLock.hpp
  Semaphore.hpp
  Thread.hpp
  ThreadLocalPointer.hpp
  Timer.hpp
)
file(GLOB ${module}_sources
  __module__.cpp
  atomic.cpp
  AutoResetEvent.cpp
  Cleanup.cpp
  ConditionVariable.cpp
  CriticalSection.cpp
  List.cpp
  ManualResetEvent.cpp
  Mutex.cpp
  Pool.cpp
  Queue.cpp
  ReadWriteLock.cpp
  Semaphore.cpp
  Thread.cpp
  ThreadLocalPointer.cpp
  Timer.cpp
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
