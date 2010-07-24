// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mt/Semaphore.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE create ( ::LONG initial, ::LONG maximum )
    {
        const ::HANDLE handle = ::CreateSemaphore(0, initial, maximum, 0);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateSemaphore, error);
        }
        return (handle);
    }

}

namespace w32 { namespace mt {

    Semaphore::Lock::Lock ( Semaphore& mutex )
        : mySemaphore(mutex)
    {
        mySemaphore.acquire();
    }

    Semaphore::Lock::Lock ( Semaphore& mutex, const Timespan& timeout )
        : mySemaphore(mutex)
    {
        if ( !mySemaphore.acquire(timeout) ) {
            throw (Timeout());
        }
    }

    Semaphore::Lock::~Lock ()
    {
        mySemaphore.release();
    }

    Semaphore::Semaphore ( long initial, long maximum )
        : Object(Object::claim(::create(initial,maximum)))
    {
    }

    void Semaphore::acquire ()
    {
        wait();
    }

    bool Semaphore::acquire ( const Timespan& timeout )
    {
        return (wait(timeout));
    }

    long Semaphore::release ( long count )
    {
        ::LONG oldcount = 0;
        if ( ::ReleaseSemaphore(handle(), count, &oldcount) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CloseHandle, error);
        }
        return (oldcount);
    }

} }
