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

#include <w32.com/Object.hpp>
#include <w32/app/in-process-server.hpp>

namespace w32 { namespace com {

    Object::Object ()
        : myReferenceCount(1)
    {
        ::InterlockedIncrement(&GlobalObjectCount);
    }

    Object::~Object ()
    {
        ::InterlockedDecrement(&GlobalObjectCount);
    }

    ::ULONG __stdcall Object::AddRef ()
    {
        return (::InterlockedIncrement(&myReferenceCount));
    }

    ::ULONG __stdcall Object::Release ()
    {
        if ( ::InterlockedDecrement(&myReferenceCount) == 0 )
        {
            delete this; return (0);
        }
        return (myReferenceCount);
    }

    ::HRESULT __stdcall Object::QueryInterface (
        const ::GUID& guid, void ** object
        )
    {
        (*object) = query< ::IUnknown >(guid);
        return ((*object) == 0)? E_NOINTERFACE : S_OK;
    }

} }
