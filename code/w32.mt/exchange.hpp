#ifndef _w32_mt_exchange_hpp__
#define _w32_mt_exchange_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace mt {

    inline ::LONG exchange ( volatile ::LONG& x, ::LONG y )
    {
        return InterlockedExchange(&x, y);
    }

    inline ::LONGLONG exchange ( volatile ::LONGLONG& x, ::LONGLONG y )
    {
        return InterlockedExchange64(&x, y);
    }

    inline ::PVOID exchange ( volatile ::PVOID& x, ::PVOID y )
    {
        return InterlockedExchangePointer(&x, y);
    }

    inline ::LONG exchange_acquire ( volatile ::LONG& x, ::LONG y )
    {
#if defined(_M_IA64)
        return InterlockedExchangeAcquire(&x, y);
#else
        return exchange(x, y);
#endif
    }

    inline ::LONGLONG exchange_acquire ( volatile ::LONGLONG& x, ::LONGLONG y )
    {
#if defined(_M_IA64)
        return InterlockedExchangeAcquire64(&x, y);
#else
        return exchange(x, y);
#endif
    }

    inline ::PVOID exchange_acquire ( volatile ::PVOID& x, ::PVOID y )
    {
#if defined(_M_IA64)
        return InterlockedExchangePointerAcquire(&x, y);
#else
        return exchange(x, y);
#endif
    }

} }

#endif /* _w32_mt_exchange_hpp__ */
