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
#include <w32.io/InputStream.hpp>
#include <w32/Error.hpp>

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

    void Transfer::clear ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    bool Transfer::done () const
    {
        return (HasOverlappedIoCompleted(&myData));
    }

    dword Transfer::finish ( InputStream stream )
    {
        dword xferred = 0;
        const ::BOOL result = ::GetOverlappedResult
            (stream.handle(), &myData, &xferred, TRUE);
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetOverlappedResult, error);
        }
        return (xferred);
    }

} }
