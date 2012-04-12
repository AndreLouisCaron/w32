#################################################
  w32++: Modern C++ bindings for the Win32 API.
#################################################

:author: Andre Caron (andre.l.caron@gmail.com)

Introduction
============

This library is intended to help you write all those nitty-gritty Windows-only
programs and features that require an intimate relationship with the platform:
services, shell extensions and scripting of Windows components (such as the task
scheduler) to name a few.

Although there is some feature overlap with .NET, Boost or Qt, it is not an
alternative to these frameworks.  Rather, it gives you the tools you need to
write those extra platform-specific features not covered by these frameworks.

Project state
=============

I've been working on this project in my spare time since 2006.  I'm in the
process of assembling all the code I wrote into this project and there are
still some large-scale design issues to resolve.  There is active development
in several core components.  Therefore, you should not expect backwards
compatibility for the next few minor releases.

Getting started
===============

1. Get the source code.

   ::

      git clone git://github.com/AndreLouisCaron/w32.git
      cd w32
      git submodule init
      git submodule update

2. Generate build scripts.

   ::

      mkdir work
      cd work
      cmake -G "NMake Makefiles" ..

   If you prefer to use Visual Studio, generate a solution using one of the
   Visual Studio solution generators built-in to CMake.  Type ``cmake`` on
   the command line for a list of supported Visual Studio versions.

3. Compile the libraries and demo projects.

   ::

      nmake

   If you generated Visual Studio solution instead of the Makefiles, start
   Visual Studio, open the solution and build the project (``Ctrl+Shift+B``
   hotkey).

4. Build the API documentation.

   ::

      nmake help

Embedding
---------

This library is designed to be easily embedded into other CMake projects.  When
built as a dependency, the demo projects, test suites and API documentation are
not compiled.  Further, you can compile only the parts of the library you
intend to use.

    ::

       project(fubar)

       # Tell CMake where to resolve the w32 library.  If you linked it as a
       # Git submodule under "libs/w32", you can do something like this:
       set(w32_DIR
         ${CMAKE_CURRENT_SOURCE_DIR}/libs/w32
       )

       # Add w32 library targets.  Specify a subset of the w32 sub-libraries
       # using the CMake components feature or select all libraries by
       # omitting the list (e.g. use only "find_package(w32)").
       find_package(w32
         COMPONENTS
           w32
           w32.io
           w32.mt
       )

       # Write some program depending on the w32 libraries.
       set(sources
         fubar.cpp
       )
       add_executable(fubar ${sources})

       # Have this program link against the w32 libraries.
       target_link_libraries(fubar
         w32 w32.io w32.mt
       )

       # Make sure CMake knows to build the w32 libraries first.
       add_dependencies(fubar
         w32 w32.io w32.mt
       )
       

License
=======

This software is free for use in open source and commercial/closed-source
applications so long as you respect the terms of this 2-clause BSD license:

> Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
> All rights reserved.
>
> Redistribution and use in source and binary forms, with or without
> modification, are permitted provided that the following conditions are
> met:
>
>  * Redistributions of source code must retain the above copyright
>    notice, this list of conditions and the following disclaimer.
>
>  * Redistributions in binary form must reproduce the above copyright
>    notice, this list of conditions and the following disclaimer in the
>    documentation and/or other materials provided with the distribution.
>
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
> "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
> LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
> A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
> HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
> SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
> LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
> DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
> THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
> (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
> OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

If you use and like this software, please let me know.  If you are willing to
announce it publicly, I can add you to a list of known users.  Such a list
usually helps in attracting attention and giving the project more credibility,
ensuring it keeps growing and stays bug free!
