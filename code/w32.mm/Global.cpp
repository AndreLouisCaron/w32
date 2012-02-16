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

#include <w32.mm/Global.hpp>
#include <w32/Error.hpp>

namespace {

    ::HGLOBAL allocate ( ::SIZE_T bytes )
    {
        const ::HGLOBAL handle = ::GlobalAlloc(GMEM_ZEROINIT,bytes);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalAlloc, error);
        }
        return (handle);
    }

    void abandon ( ::HGLOBAL object ) {}
    void destroy ( ::HGLOBAL object )
    {
        const ::HGLOBAL result = ::GlobalFree(object);
        if ( result != 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalFree, error);
        }
    }

}

namespace w32 { namespace mm {

    Global::Handle Global::claim ( ::HGLOBAL object )
    {
        return (Handle(object, &::destroy));
    }

    Global::Handle Global::proxy ( ::HGLOBAL object )
    {
        return (Handle(object, &::abandon));
    }

    Global::Global ( size_t bytes )
        : myHandle(claim(::allocate(bytes)))
    {
    }

    const Global::Handle& Global::handle () const
    {
        return (myHandle);
    }

    Global::Lock::Lock ( Global& object )
        : myLocation(::GlobalLock(object.handle()))
    {
        if ( myLocation == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalLock, error);
        }
    }

    Global::Lock::~Lock ()
    {
        if ( ::GlobalUnlock(myLocation) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalUnlock, error);
        }
    }

    void * Global::Lock::location () const
    {
        return (myLocation);
    }

    std::size_t Global::size () const
    {
        const ::SIZE_T result = ::GlobalSize(handle());
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalSize, error);
        }
        return (result);
    }

} }
