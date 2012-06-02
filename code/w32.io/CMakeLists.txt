# Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  AnonymousPipe.hpp
  Channel.hpp
  CompletionPort.hpp
  ConsoleInput.hpp
  ConsoleOutput.hpp
  Folder.hpp
  InputFile.hpp
  InputStream.hpp
  NamedPipe.hpp
  Notification.hpp
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
  AnonymousPipe.cpp
  Channel.cpp
  CompletionPort.cpp
  ConsoleInput.cpp
  ConsoleOutput.cpp
  Folder.cpp
  InputFile.cpp
  InputStream.cpp
  NamedPipe.cpp
  Notification.cpp
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
