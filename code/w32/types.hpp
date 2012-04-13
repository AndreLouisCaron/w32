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
    typedef ::USHORT ushort;

    /*! @brief 8-bit (1-byte) unsigned integer. */
    typedef ::BYTE byte;

    /*! @brief 16-bit (2-byte) unsigned integer. */
    typedef ::WORD word;

    /*! @brief 32-bit (4-byte) unsigned integer. */
    typedef ::DWORD dword;

    /*! @brief 64-bit (8-byte) unsigned integer. */
    typedef ::DWORDLONG qword;

    typedef ::LRESULT lresult;
    typedef ::WPARAM wparam;
    typedef ::LPARAM lparam;

    /*! @brief 8-bit (1-byte) signed integer. */
    typedef __int8 int8;

    /*! @brief 16-bit (2-byte) signed integer. */
    typedef __int16 int16;

    /*! @brief 32-bit (4-byte) signed integer. */
    typedef __int32 int32;

    /*! @brief 64-bit (8-byte) signed integer. */
    typedef __int64 int64;

    /*! @brief 8-bit (1-byte) unsigned integer. */
    typedef byte uint8;

    /*! @brief 16-bit (2-byte) unsigned integer. */
    typedef word uint16;

    /*! @brief 32-bit (4-byte) unsigned integer. */
    typedef dword uint32;

    /*! @brief 64-bit (8-byte) unsigned integer. */
    typedef qword uint64;

    /*!
     * @brief Signed integer the size of a pointer.
     */
    typedef ::INT_PTR intptr;

    /*!
     * @brief Unsigned integer the size of a pointer.
     */
    typedef ::UINT_PTR uintptr;

    /*!
     * @brief Portable integer the size of a pointer.
     *
     * Used for pointer arithmetic.  This is the previledged type for portable
     * code between 32-bit and 64-bit machines as the compiler expands it to
     * the proper size.
     */
    typedef ::ULONG_PTR ulongptr;

    typedef ::LPVOID pointer;

    /*!
     * @brief Unsigned integer type, with @c sizeof(size_t)==sizeof(pointer).
     */
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
