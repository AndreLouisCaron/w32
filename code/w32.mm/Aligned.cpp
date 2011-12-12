// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mm/Aligned.hpp>
#include <malloc.h>
#include <memory>
#include <cstddef>
#include <stdexcept>

namespace {

    bool ispowerof2 ( w32::size_t x ) {
        return ( (x != 0) && ((x & (x-1)) == 0) );
    }

}

namespace w32 { namespace mm {

    bool Aligned::supports ( size_t alignment )
    {
        return (ispowerof2(alignment));
    }

    Aligned::Aligned ( size_t alignment )
        : myAlignment(alignment)
    {
        if ( !supports(alignment) ) {
            throw (std::invalid_argument("Aligned"));
        }
    }

    void * Aligned::acquire ( size_t amount )
    {
        return (::_aligned_malloc(amount, myAlignment));
    }

    void Aligned::release ( void * start, size_t )
    {
        ::_aligned_free(start);
    }

} }
