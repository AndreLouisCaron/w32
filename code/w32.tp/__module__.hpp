#ifndef _w32_tp_hpp__
#define _w32_tp_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"

namespace w32 {
    namespace tp {}
}

/*!
 * @defgroup w32-tp New thread pool API.
 *
 * This group contains a generalized threading API for programs using an
 * asynchronous design.  Thread pools support CPU-bound work, I/O-bound work,
 * waiting for kernel objects (e.g. synchronization objects and external
 * processes) and timers.  The thread pool manages thread creation and
 * destruction and attemps to make efficient use of system resources.  For
 * example, wait for kernel objects are grouped in bundles of @c
 * MAXIMUM_WAIT_OBJECTS to ensure minimal overhead.  Remember that this pool is
 * designed by experts with deep knowledge of Windows internals and it may be
 * very hard to beat them at efficient use of threads.
 *
 * @see http://msdn.microsoft.com/en-us/library/windows/desktop/ms686760.aspx
 */

#if (_WIN32_WINNT >= 0x600)
#  include <w32.tp/Cleanup.hpp>
#  include <w32.tp/Hints.hpp>
#  include <w32.tp/Timer.hpp>
#  include <w32.tp/Transfer.hpp>
#  include <w32.tp/Wait.hpp>
#  include <w32.tp/Work.hpp>
#  include <w32.tp/Pool.hpp>
#  include <w32.tp/Queue.hpp>
#endif

#endif /* _w32_tp_hpp__ */
