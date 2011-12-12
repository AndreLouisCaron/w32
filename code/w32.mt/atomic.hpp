#ifndef _w32_mt_atomic_hpp__
#define _w32_mt_atomic_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace mt {

    template<typename> class atomic;

    template<> class atomic<int32>
    {
        volatile ::LONG myValue; // has to be aligned!
    public:
        atomic<int32>& operator++ ()
        {
            ::InterlockedIncrement(&myValue);
            return (*this);
        }
        atomic<int32>& operator-- ()
        {
            ::InterlockedDecrement(&myValue);
            return (*this);
        }
        operator int32 () const
        {
            return (static_cast<int32>(myValue));
        }
    };

    template<> class atomic<int64>
    {
        volatile ::LONGLONG myValue; // has to be aligned!
    public:
        atomic<int64>& operator++ ()
        {
            ::InterlockedIncrement64(&myValue);
            return (*this);
        }
        atomic<int64>& operator-- ()
        {
            ::InterlockedDecrement64(&myValue);
            return (*this);
        }
        operator int64 () const
        {
            return (static_cast<int64>(myValue));
        }
    };

    template<> class atomic<void*>
    {
        volatile ::PVOID myValue; // has to be aligned!
    public:
        atomic ( void * value = 0 )
            : myValue(value)
        {
        }

        void * swapif ( void * comparand, void * substitute )
        {
            return ::InterlockedCompareExchangePointer
                (&myValue, substitute, comparand);
        }

        operator void* () const
        {
            return (myValue);
        }
    };

} }

#endif /* _w32_mt_atomic_hpp__ */
