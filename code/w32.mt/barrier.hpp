#ifndef _w32_mt_barrier_hpp__
#define _w32_mt_barrier_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

#include <intrin.h>

namespace w32 { namespace mt {

    inline void read_barrier ()
    {
#ifndef NO_BARRIER
        _ReadBarrier();
#endif
    }

    inline void write_barrier ()
    {
#ifndef NO_BARRIER
        _WriteBarrier();
#endif
    }

    inline void barrier ()
    {
#ifndef NO_BARRIER
        _ReadWriteBarrier();
#endif
    }

} }

#endif /* _w32_mt_barrier_hpp__ */
