#ifndef _w32_mt_decrement_hpp__
#define _w32_mt_decrement_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace mt {

    inline ::LONG decrement ( volatile ::LONG& x )
    {
        return InterlockedDecrement(&x);
    }

    inline ::LONGLONG decrement ( volatile ::LONGLONG& x )
    {
        return InterlockedDecrement64(&x);
    }

    inline ::LONG decrement_acquire ( volatile ::LONG& x )
    {
        return InterlockedDecrementAcquire(&x);
    }

#ifdef _WIN64
    inline ::LONGLONG decrement_acquire ( volatile ::LONGLONG& x )
    {
        return InterlockedDecrementAcquire64(&x);
    }
#endif

    inline ::LONG decrement_release ( volatile ::LONG& x )
    {
        return InterlockedDecrementRelease(&x);
    }

#ifdef _WIN64
    inline ::LONGLONG decrement_release ( volatile ::LONGLONG& x )
    {
        return InterlockedDecrementRelease64(&x);
    }
#endif

} }

#endif /* _w32_mt_decrement_hpp__ */
