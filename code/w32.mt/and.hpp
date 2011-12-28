#ifndef _w32_mt_and_hpp__
#define _w32_mt_and_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace mt {

    // note: 8-, 16-, 32- and 64-bit versions are available.

    inline ::LONG and ( volatile ::LONG& x, ::LONG y )
    {
#if defined(InterlockedAnd)
        return IneterlockedAnd(&x, y);
#else
        LONG i;
        LONG j;
        j = x;
        do {
            i = j;
            j = InterlockedCompareExchange(&x, i&y, i);
        }
        while (i != j);
        return j;
#endif
    }

    inline ::LONGLONG and ( volatile ::LONGLONG& x, ::LONGLONG y )
    {
        return InterlockedAnd64(&x, y);
    }


} }

#endif /* _w32_mt_and_hpp__ */
