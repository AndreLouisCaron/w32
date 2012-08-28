#ifndef _w32_mt_hpp__
#define _w32_mt_hpp__

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
    namespace mt {}
}

/*!
 * @defgroup w32-mt Multi-threading services.
 *
 * This group contains services for implementation of programs based on
 * multi-threading for efficient use of multi-processor architectures.  It
 * contains facilities for starting and controlling threads, as well as
 * synchronization primitives.
 */

#include <w32.mt/AutoResetEvent.hpp>
#include <w32.mt/CriticalSection.hpp>
#include <w32.mt/Fiber.hpp>
#include <w32.mt/ManualResetEvent.hpp>
#include <w32.mt/Mutex.hpp>
#include <w32.mt/Semaphore.hpp>
#include <w32.mt/Timer.hpp>
#include <w32.mt/Thread.hpp>
#include <w32.mt/ThreadLocalPointer.hpp>

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
#    include <w32.mt/ConditionVariable.hpp>
#    include <w32.mt/ReadWriteLock.hpp>
#endif

// TODO: propagate this on a per-symbol basis.
#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
#   include <w32.mt/and.hpp>
#   include <w32.mt/atomic.hpp>
#   include <w32.mt/barrier.hpp>
#   include <w32.mt/compare-exchange.hpp>
#   include <w32.mt/decrement.hpp>
#   include <w32.mt/exchange.hpp>
#   include <w32.mt/increment.hpp>
#   include <w32.mt/or.hpp>
#   include <w32.mt/xor.hpp>
#endif

#endif /* _w32_mt_hpp__ */
