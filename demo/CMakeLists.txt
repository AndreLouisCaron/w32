# w32/demo/CMakeLists.txt:
#   Build script for demonstration projects.

# Resolve our own libraries.
link_directories(${LIBRARY_OUTPUT_PATH})

# Build all demo projects.
set(demo-projects
  c10k-server
  code-injection
  com-instantiate
#  display-jpg
#  display-png
  dns-resolve
  event-source
  ftp-client
  hardlink
  installed-products
  junction
  key-generation
  large-file-mapping
  loaded-modules
  named-pipe-client
  named-pipe-server
  namespace-ftp
  namespace-tester
  pnm-thumbnails
  prefork-echo-server
  prefork-master
  prefork-slave
  registry
  screen-capture
  service
  sha1
  shell-ls
  splash-screen
#  stream-my-screen
  symbolic-link
  task-scheduler-1
  tcp-client
  tcp-server
  tga-thumbnails
  thread-pools
  udp-client
  udp-server
  wallpaper-swapper
)
foreach(demo-project ${demo-projects})
  add_subdirectory(${demo-project})
endforeach()
