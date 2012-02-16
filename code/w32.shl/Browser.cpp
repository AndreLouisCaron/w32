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

#include <w32.shl/Browser.hpp>

namespace w32 { namespace shl {

    Browser::Browser ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    Browser::Browser ( const Hints& hints )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.ulFlags = hints;
    }

    void Browser::title ( const w32::string& text )
    {
        myData.lpszTitle = text.data();
    }

    Path Browser::prompt ()
    {
        const ::LPCITEMIDLIST result = ::SHBrowseForFolderW(&myData);
        if ( result == 0 ) {
            return (L"");
        }
        return (Path(result));
    }

    const Browser::Hints Browser::Hints::folders ()
    {
        return (BIF_RETURNONLYFSDIRS);
    }

    Browser::Hints::Hints ( Value value )
        : myValue(value)
    {
    }

    Browser::Hints::Value Browser::Hints::value () const
    {
        return (myValue);
    }

    Browser::Hints::operator Browser::Hints::Value () const
    {
        return (myValue);
    }

    Browser::Hints& Browser::Hints::operator|= ( const Hints& rhs )
    {
        myValue |= rhs.myValue; return (*this);
    }

    Browser::Hints Browser::Hints::operator| ( const Hints& rhs )
    {
        Hints result(*this); result |= rhs; return (result);
    }

} }
