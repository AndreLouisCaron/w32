#ifndef _w32_types_hpp__
#define _w32_types_hpp__

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

#include "__configure__.hpp"
#include <cstddef>

namespace w32 {

    typedef ::UINT uint;
    typedef ::ULONG ulong;

    typedef ::BYTE byte;
    typedef ::WORD word;
    typedef ::DWORD dword;
    typedef ::DWORDLONG qword;

    typedef ::LRESULT lresult;
    typedef ::WPARAM wparam;
    typedef ::LPARAM lparam;

        // Resort to compiler extensions for now.
    typedef __int8 int8;
    typedef __int16 int16;
    typedef __int32 int32;
    typedef __int64 int64;

    typedef byte uint8;
    typedef word uint16;
    typedef dword uint32;
    typedef qword uint64;

    typedef ::INT_PTR intptr;
    typedef ::UINT_PTR uintptr;
    typedef ::ULONG_PTR ulongptr;

    typedef ::LPVOID pointer;

    typedef ::SIZE_T size_t;

        // Cool cast to any pointer type!
    static struct {
        template<typename T> operator T* () const { return (0); }
        template<typename T>
        bool operator== ( const T * rhs ) const { return (rhs == 0); }
        template<typename T>
        bool operator!= ( const T * rhs ) const { return (rhs != 0); }
        operator bool () const { return (false); }
        bool operator! () const { return (true); }
    } const null;

    typedef ::HRESULT hresult;
    typedef ::HWND hwnd;

}

#endif /* _w32_types_hpp__ */
