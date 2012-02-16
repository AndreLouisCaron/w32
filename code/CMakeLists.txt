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

set(modules
  w32
  w32.com
  w32.cr
  w32.dbg
  w32.fs
  w32.gdi
  w32.in
  w32.io
  w32.ipc
  w32.mm
  w32.msi
  w32.mt
  w32.net
  w32.net.ipv4
  w32.net.ipv6
  w32.net.tcp
  w32.net.udp
  w32.rgs
  w32.sc
  w32.shl
  w32.shl.ext
  w32.sy
  w32.tp
  w32.ts-1
  w32.ts-2
  w32.xml.dom
  w32.xml.sax
)

set(w32_dependencies)
set(w32.com_dependencies w32)
set(w32.cr_dependencies w32)
set(w32.dbg_dependencies w32)
set(w32.fs_dependencies w32)
set(w32.gdi_dependencies w32)
set(w32.in_dependencies w32)
set(w32.io_dependencies w32)
set(w32.ipc_dependencies w32)
set(w32.mm_dependencies w32)
set(w32.msi_dependencies w32)
set(w32.mt_dependencies w32)
set(w32.net_dependencies w32)
set(w32.net.ipv4_dependencies w32 w32.net)
set(w32.net.ipv6_dependencies w32 w32.net)
set(w32.net.tcp_dependencies w32 w32.net w32.net.ipv4)
set(w32.net.udp_dependencies w32 w32.net w32.net.ipv4)
set(w32.rgs_dependencies w32)
set(w32.sc_dependencies w32)
set(w32.shl_dependencies w32 w32.com)
set(w32.shl.ext_dependencies w32 w32.com w32.shl)
set(w32.sy_dependencies w32)
set(w32.tp_dependencies w32 w32.mt)
set(w32.ts-1_dependencies w32 w32.com)
set(w32.ts-2_dependencies w32 w32.com)
set(w32.xml.dom_dependencies w32 w32.com)
set(w32.xml.sax_dependencies w32 w32.com)

# Select modules to build.
if(w32_FIND_COMPONENTS)
  # If a subset of modules was selected, build only
  # those modules and their dependencies.
  foreach(module ${w32_FIND_COMPONENTS})
    set(build_${module} 1)
    foreach(dependency ${${module}_dependencies})
       set(build_${dependency} 1)
    endforeach()
  endforeach()
else()
  # No specific modules were selected, build everything!
  foreach(module ${modules})
    set(build_${module} 1)
  endforeach()
endif()

# Build selected modules.
foreach(module ${modules})
  if(${build_${module}})
    add_subdirectory(${module})
  endif()
  # Special symbol for easy linking to the library and its dependencies.
  set(${module}_library ${module} ${${module}_dependencies})
endforeach()
