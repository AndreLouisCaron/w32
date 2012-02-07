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
#include <w32.io/Transfer.hpp>
#include <w32/Error.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace io {

    InputStream::InputStream ( const Handle& handle )
        : Stream(handle)
    {
    }

    dword InputStream::get ( void * data, dword size )
    {
        ::DWORD xferred = 0;
        const ::BOOL result = ::ReadFile(
            handle(), data, size, &xferred, 0
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if (error == ERROR_BROKEN_PIPE) {
                return (0);
            }
            UNCHECKED_WIN32C_ERROR(ReadFile, error);
        }
        return (xferred);
    }

    bool InputStream::get
        ( void * data, dword size, Transfer& xfer, dword& xferred )
    {
        const ::BOOL result = ::ReadFile(
            handle(), data, size, &xferred, &xfer.data()
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if (error == ERROR_IO_PENDING) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(ReadFile, error);
        }
        return (true);
    }

    InputStream::operator w32::Waitable () const
    {
        return (w32::Waitable(handle()));
    }

} }
