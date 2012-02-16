// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
