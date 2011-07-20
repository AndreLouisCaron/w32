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


#include "../__compiler-intro__.hpp"
#   include <w32/mt/AutoResetEvent.hpp>
#   include <w32/mt/CriticalSection.hpp>
#   include <w32/mt/ManualResetEvent.hpp>
#   include <w32/mt/Mutex.hpp>
#   include <w32/mt/Semaphore.hpp>
#   include <w32/mt/Thread.hpp>
#   include <w32/mt/ThreadLocalPointer.hpp>
#   if (_WIN32_WINNT >= 0x600)
#       include <w32/mt/ConditionVariable.hpp>
#       include <w32/mt/ReadWriteLock.hpp>
#       include <w32/mt/Pool.hpp>
#       include <w32/mt/Queue.hpp>
#       include <w32/mt/Cleanup.hpp>
#   endif
#include "../__compiler-outro__.hpp"

#endif /* _w32_mt_hpp__ */
