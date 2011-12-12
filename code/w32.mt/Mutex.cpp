// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mt/Mutex.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( ::LPCWSTR name )
    {
        const ::HANDLE result = ::CreateMutexW(0, FALSE, name);
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateMutex, error);
        }
        return (result);
    }

    ::HANDLE find ( ::LPCWSTR name )
    {
        const ::HANDLE result = ::OpenMutexW(0, FALSE, name);
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateMutex, error);
        }
        return (result);
    }

}

namespace w32 { namespace mt {

    Mutex::Lock::Lock ( Mutex& mutex )
        : myMutex(mutex)
    {
        myMutex.acquire();
    }

    Mutex::Lock::Lock ( Mutex& mutex, const Timespan& timeout )
        : myMutex(mutex)
    {
        if ( !myMutex.acquire(timeout) ) {
            throw (Waitable::Timeout());
        }
    }

    Mutex::Lock::~Lock ()
    {
        myMutex.release();
    }

    Mutex Mutex::open ( const string& name )
    {
        const Handle handle(::find(name.data()));
        return (Mutex(handle));
    }

    Mutex::Mutex ( const Handle& handle )
        : Object(handle)
    {
    }

    Mutex::Mutex ()
        : Object(Object::claim(::allocate(0)))
    {
    }

    Mutex::Mutex ( const string& name )
        : Object(Object::claim(::allocate(name.data())))
    {
    }

    void Mutex::acquire ()
    {
        Waitable(*this).wait();
    }

    bool Mutex::acquire ( const Timespan& timeout )
    {
        return (Waitable(*this).wait(timeout));
    }

    void Mutex::release ()
    {
        const ::BOOL result = ::ReleaseMutex(handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ReleaseMutex, error);
        }
    }

    Mutex::operator Waitable () const
    {
        return Waitable(handle());
    }

} }
