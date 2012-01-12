// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/Transfer.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/Transfer.hpp>

namespace w32 { namespace io {

    Transfer::Transfer ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    Transfer::Data& Transfer::data ()
    {
        return (myData);
    }

    const Transfer::Data& Transfer::data () const
    {
        return (myData);
    }

    bool Transfer::complete () const
    {
        return (HasOverlappedIoCompleted(&myData));
    }

} }
