#ifndef _w32_mt_compare_exchange_hpp__
#define _w32_mt_compare_exchange_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace mt {

    inline ::LONG compare_exchange
        ( ::LONG z, volatile ::LONG& x, ::LONG y )
    {
        return InterlockedCompareExchange(&x, y, z);
    }

    inline ::LONGLONG compare_exchange
        ( ::LONGLONG z, volatile ::LONGLONG& x, ::LONGLONG y )
    {
        return InterlockedCompareExchange64(&x, y, z);
    }

    inline ::PVOID compare_exchange
        ( ::PVOID z, volatile ::PVOID& x, ::PVOID y )
    {
        return InterlockedCompareExchangePointer(&x, y, z);
    }

    inline ::LONG compare_exchange_acquire
        ( ::LONG z, volatile ::LONG& x, ::LONG y )
    {
        return InterlockedCompareExchangeAcquire(&x, y, z);
    }

    inline ::LONGLONG compare_exchange_acquire
        ( ::LONGLONG z, volatile ::LONGLONG& x, ::LONGLONG y )
    {
        return InterlockedCompareExchangeAcquire64(&x, y, z);
    }

    inline ::PVOID compare_exchange_acquire
        ( ::PVOID z, volatile ::PVOID& x, ::PVOID y )
    {
        return InterlockedCompareExchangePointerAcquire(&x, y, z);
    }

} }

#endif /* _w32_mt_compare_exchange_hpp__ */
