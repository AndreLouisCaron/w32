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

#include <w32.rgs/Keys.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace rgs {

    Keys::Keys ( const Key& key )
        : myKey(key), myIndex(0), myResult(ERROR_SUCCESS)
    {
        myName[0] = L'\0';
    }

    const wchar_t * Keys::result () const
    {
        return (myName);
    }

    bool Keys::next ()
    {
        myName[0] = L'\0';
        dword length = 255;
        myResult = ::RegEnumKeyExW(
            myKey.handle(), myIndex, myName, &length, 0, 0, 0, 0
            );
        if ( myResult == ERROR_NO_MORE_ITEMS ) {
            return (false);
        }
        ++myIndex;
        if ( myResult != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegEnumKeyEx,myResult);
        }
        myName[length] = L'\0';
        return (true);
    }

} }
