// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mt/AutoResetEvent.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( const wchar_t * name )
    {
        const ::HANDLE handle = ::CreateEventW(0, FALSE, 0, name);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateEvent, error);
        }
        return (handle);
    }

    ::HANDLE find ( const wchar_t * name )
    {
        const ::HANDLE handle = ::CreateEventW(0, FALSE, 0, name);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateEvent, error);
        }
        return (handle);
    }

}

namespace w32 { namespace mt {

    AutoResetEvent AutoResetEvent::open ( const string& name )
    {
        const Handle handle(Object::claim(::find(name.c_str())));
        return (AutoResetEvent(handle));
    }

    AutoResetEvent::AutoResetEvent ( const Handle& handle )
        : Object(handle)
    {
    }

    AutoResetEvent::AutoResetEvent ()
        : Object(Object::claim(::allocate(0)))
    {
    }

    AutoResetEvent::AutoResetEvent ( const string& name )
        : Object(Object::claim(::allocate(name.data())))
    {
    }

    void AutoResetEvent::set ()
    {
        const ::BOOL result = ::SetEvent(handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetEvent, error);
        }
    }

    AutoResetEvent::operator Waitable () const
    {
        return Waitable(handle());
    }

} }
