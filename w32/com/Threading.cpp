// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <com/Threading.hpp>

namespace w32{ namespace com {

    const Threading Threading::appartment ()
    {
        return (Threading(COINIT_APARTMENTTHREADED));
    }

    const Threading Threading::multiple ()
    {
        return (Threading(COINIT_MULTITHREADED));
    }

    Threading::Threading ( Value value )
        : myValue(value)
    {
    }

    Threading::Value Threading::value () const
    {
        return (myValue);
    }

} }
