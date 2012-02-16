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

#include <w32.mm/Virtual.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace mm {

    const Virtual::Access Virtual::Access::e ()
    {
        return (PAGE_EXECUTE);
    }

    const Virtual::Access Virtual::Access::r ()
    {
        return (PAGE_READONLY);
    }

    const Virtual::Access Virtual::Access::rw ()
    {
        return (PAGE_READWRITE);
    }

    const Virtual::Access Virtual::Access::re ()
    {
        return (PAGE_EXECUTE_READ);
    }

    const Virtual::Access Virtual::Access::rwe ()
    {
        return (PAGE_EXECUTE_READWRITE);
    }

    Virtual::Virtual ( const Access& access )
        : myAccess(access)
    {
    }

    void * Virtual::acquire ( size_t amount )
    {
        const ::LPVOID location = ::VirtualAlloc(
            0, amount, MEM_RESERVE|MEM_COMMIT, myAccess.value()
            );
        if ( location == 0 ) {
            UNCHECKED_WIN32C_ERROR(VirtualAlloc,::GetLastError());
        }
        return (location);
    }

    void Virtual::release ( const void * location, size_t )
    {
        const ::BOOL result = ::VirtualFree(
            const_cast<::LPVOID>(location), 0, MEM_RELEASE
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(VirtualFree,::GetLastError());
        }
    }

} }
