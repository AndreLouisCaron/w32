// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mt/ManualResetEvent.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( const wchar_t * name )
    {
        const ::HANDLE handle = ::CreateEventW(0, TRUE, 0, name);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateEvent, error);
        }
        return (handle);
    }

    ::HANDLE find ( const wchar_t * name )
    {
        const ::HANDLE handle = ::OpenEventW(0, FALSE, name);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateEvent, error);
        }
        return (handle);
    }

}

namespace w32 { namespace mt {

    ManualResetEvent ManualResetEvent::open ( const string& name )
    {
        const Handle handle(claim(::find(name.c_str())));
        return (ManualResetEvent(handle));
    }

    ManualResetEvent::ManualResetEvent ( const Handle& handle )
        : Object(handle)
    {
    }

    ManualResetEvent::ManualResetEvent ()
        : Object(Object::claim(::allocate(0)))
    {
    }

    ManualResetEvent::ManualResetEvent ( const string& name )
        : Object(Object::claim(::allocate(name.c_str())))
    {
    }

    void ManualResetEvent::set ()
    {
        if ( ::SetEvent(handle()) == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SetEvent,::GetLastError());
        }
    }

    void ManualResetEvent::reset ()
    {
        if ( ::ResetEvent(handle()) == FALSE ) {
            UNCHECKED_WIN32C_ERROR(ResetEvent,::GetLastError());
        }
    }

    void ManualResetEvent::wait () const
    {
        Waitable(*this).wait();
    }

    bool ManualResetEvent::wait ( const Timespan& timeout ) const
    {
        return (Waitable(*this).wait(timeout));
    }

    bool ManualResetEvent::test () const
    {
        return (Waitable(*this).test());
    }

    ManualResetEvent::operator Waitable () const
    {
        return Waitable(handle());
    }

} }
