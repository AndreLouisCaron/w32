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
  message(STATUS "Module '${module}': ${build_${module}}.")
  if(${build_${module}})
    add_subdirectory(${module})
  endif()
  # Special symbol for easy linking to the library and its dependencies.
  set(${module}_library ${module} ${${module}_dependencies})
endforeach()
