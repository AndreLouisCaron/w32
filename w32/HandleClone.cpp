// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/HandleClone.hpp>
#include <w32/dbg/UncheckedError.hpp>

namespace {

    ::HANDLE clone ( ::HANDLE handle, ::HANDLE sprocess, ::HANDLE tprocess )
    {
        ::HANDLE duplicate = INVALID_HANDLE_VALUE;
        const ::BOOL result = ::DuplicateHandle(
            sprocess, handle, tprocess, &duplicate,
            0, FALSE, DUPLICATE_SAME_ACCESS
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(DuplicateHandle, ::GetLastError());
        }
        return (duplicate);
    }

    ::HANDLE clone ( ::HANDLE handle, ::HANDLE process )
    {
        return (clone(handle, process, process));
    }

    ::HANDLE clone ( ::HANDLE handle )
    {
        return (clone(handle, ::GetCurrentProcess()));
    }

}

namespace w32 {

    HandleClone::HandleClone ( Value value )
        : myValue(clone(value))
    {
    }

    HandleClone::~HandleClone ()
    {
        const ::BOOL result = ::CloseHandle(myValue);
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(CloseHandle, ::GetLastError());
        }
    }

    HandleClone::Value HandleClone::value () const
    {
        return (myValue);
    }

}
