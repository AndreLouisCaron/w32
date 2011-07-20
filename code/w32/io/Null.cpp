// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/io/Null.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE open ()
    {
        const ::HANDLE console = ::CreateFileW(
            L"\\\\.\\NUL", GENERIC_READ|GENERIC_WRITE,
            FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0
            );
        if ( console == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateFile, error);
        }
        return (console);
    }

}

namespace w32 { namespace io {

    Null::Null ()
        : Channel(Object::claim(::open()))
    {
    }

} }
