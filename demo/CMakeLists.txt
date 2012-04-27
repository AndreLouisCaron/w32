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
  http-server
  ident
  ident-client
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
  self-signed-certificate
  service
  sha1
  shell-ls
  splash-screen
  ssl
#  stream-my-screen
  symbolic-link
  sy-authenticate
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
