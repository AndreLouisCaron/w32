// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.io/StandardError.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE get ()
    {
        const ::HANDLE handle = ::GetStdHandle(STD_ERROR_HANDLE);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetStdHandle, error);
        }
        return (handle);
    }

    ::HANDLE set ( ::HANDLE replacement )
    {
        const ::HANDLE current = get();
        if ( ::SetStdHandle(STD_ERROR_HANDLE,replacement) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetStdHandle, error);
        }
        return (current);
    }

}

namespace w32 { namespace io {

    StandardError::Redirection::Redirection ( OutputStream& output )
        : myPredecessor(set(output.handle()))
    {
    }

    StandardError::Redirection::~Redirection ()
    {
        set(myPredecessor);
    }

    StandardError::StandardError ()
        : OutputStream(Object::claim(::get()))
    {
    }

} }
