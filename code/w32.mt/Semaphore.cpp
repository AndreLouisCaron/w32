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

#include <w32.mt/Semaphore.hpp>
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
            throw (Waitable::Timeout());
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
        Waitable(*this).wait();
    }

    bool Semaphore::acquire ( const Timespan& timeout )
    {
        return (Waitable(*this).wait(timeout));
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

    Semaphore::operator Waitable () const
    {
        return Waitable(handle());
    }

} }
