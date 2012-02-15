#ifndef _w32_mt_hpp__
#define _w32_mt_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
#include <w32.mt/ManualResetEvent.hpp>
#include <w32.mt/Mutex.hpp>
#include <w32.mt/Semaphore.hpp>
#include <w32.mt/Thread.hpp>
#include <w32.mt/ThreadLocalPointer.hpp>
#if (_WIN32_WINNT >= 0x600)
#    include <w32.mt/ConditionVariable.hpp>
#    include <w32.mt/ReadWriteLock.hpp>
#endif

#include <w32.mt/increment.hpp>
#include <w32.mt/decrement.hpp>

#endif /* _w32_mt_hpp__ */
