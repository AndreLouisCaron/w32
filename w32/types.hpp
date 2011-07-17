#ifndef _w32_types_hpp__
#define _w32_types_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
