// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/ConsoleInput.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/ConsoleInput.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE open ()
    {
        const ::HANDLE console = ::CreateFileW(
            L"\\\\.\\CON", GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0
            );
        if ( console == INVALID_HANDLE_VALUE ) {
            UNCHECKED_WIN32C_ERROR(CreateFile,::GetLastError());
        }
        return (console);
    }

}

namespace w32 { namespace io {

    ConsoleInput::ConsoleInput ()
        : InputStream(Object::claim(::open()))
    {
    }

    ConsoleInput::operator Waitable () const
    {
        return Waitable(handle());
    }

} }
