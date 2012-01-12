// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/InputStream.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/InputStream.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace io {

    InputStream::InputStream ( const Handle& handle )
        : Stream(handle)
    {
    }

    dword InputStream::get ( byte * buffer, dword bytes )
    {
        ::DWORD read = 0;
        const ::BOOL result = ::ReadFile(
            handle(), buffer, bytes, &read, 0
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ReadFile, error);
        }
        return (read);
    }

} }
