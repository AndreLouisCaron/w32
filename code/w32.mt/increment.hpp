#ifndef _w32_mt_increment_hpp__
#define _w32_mt_increment_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace mt {

    inline ::LONG increment ( volatile ::LONG& x )
    {
        return InterlockedIncrement(&x);
    }

    inline ::LONGLONG increment ( volatile ::LONGLONG& x )
    {
        return InterlockedIncrement64(&x);
    }

    inline ::LONG increment_acquire ( volatile ::LONG& x )
    {
        return InterlockedIncrementAcquire(&x);
    }

#ifdef _M_IA64
    inline ::LONGLONG increment_acquire ( volatile ::LONGLONG& x )
    {
        return InterlockedIncrementAcquire64(&x);
    }
#endif

    inline ::LONG increment_release ( volatile ::LONG& x )
    {
        return InterlockedIncrementRelease(&x);
    }

#ifdef _M_IA64
    inline ::LONGLONG increment_release ( volatile ::LONGLONG& x )
    {
        return InterlockedIncrementRelease64(&x);
    }
#endif

} }

#endif /* _w32_mt_increment_hpp__ */
