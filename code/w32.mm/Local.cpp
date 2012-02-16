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

#include <w32.mm/Local.hpp>
#include <w32/Error.hpp>

namespace {

    ::HGLOBAL allocate ( ::SIZE_T bytes )
    {
        const ::HGLOBAL handle = ::LocalAlloc(LMEM_ZEROINIT,bytes);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalAlloc, error);
        }
        return (handle);
    }

    void abandon ( ::HGLOBAL object ) {}
    void destroy ( ::HGLOBAL object )
    {
        const ::HGLOBAL result = ::LocalFree(object);
        if ( result != 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalFree, error);
        }
    }

}

namespace w32 { namespace mm {

    Local::Handle Local::claim ( ::HGLOBAL object )
    {
        return (Handle(object, &::destroy));
    }

    Local::Handle Local::proxy ( ::HGLOBAL object )
    {
        return (Handle(object, &::abandon));
    }

    Local::Local ( size_t bytes )
        : myHandle(claim(::allocate(bytes)))
    {
    }

    const Local::Handle& Local::handle () const
    {
        return (myHandle);
    }

    Local::Lock::Lock ( Local& object )
        : myLocation(::LocalLock(object.handle()))
    {
        if ( myLocation == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalLock, error);
        }
    }

    Local::Lock::~Lock ()
    {
        if ( ::LocalUnlock(myLocation) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalUnlock, error);
        }
    }

    void * Local::Lock::location () const
    {
        return (myLocation);
    }

    std::size_t Local::size () const
    {
        const ::SIZE_T result = ::LocalSize(handle());
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalSize, error);
        }
        return (result);
    }

} }
