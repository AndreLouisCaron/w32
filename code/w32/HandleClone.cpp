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

#include <w32/HandleClone.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE clone ( ::HANDLE handle, ::HANDLE sprocess, ::HANDLE tprocess )
    {
        ::HANDLE duplicate = INVALID_HANDLE_VALUE;
        const ::BOOL result = ::DuplicateHandle(
            sprocess, handle, tprocess, &duplicate,
            0, FALSE, DUPLICATE_SAME_ACCESS
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(DuplicateHandle, ::GetLastError());
        }
        return (duplicate);
    }

    ::HANDLE clone ( ::HANDLE handle, ::HANDLE process )
    {
        return (clone(handle, process, process));
    }

    ::HANDLE clone ( ::HANDLE handle )
    {
        return (clone(handle, ::GetCurrentProcess()));
    }

}

namespace w32 {

    HandleClone::HandleClone ( Value value )
        : myValue(clone(value))
    {
    }

    HandleClone::~HandleClone ()
    {
        const ::BOOL result = ::CloseHandle(myValue);
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(CloseHandle, ::GetLastError());
        }
    }

    HandleClone::Value HandleClone::value () const
    {
        return (myValue);
    }

}
