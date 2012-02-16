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

#include <w32/mstring.hpp>

namespace w32 {

    mstring::mstring ( const string::box& data )
        : myData(data)
    {
    }

    mstring::mstring ( const string& data )
        : myData(data)
    {
    }

    mstring::mstring ( const wchar_t * data )
        : myData(data)
    {
    }

    mstring::mstring ( const mstring& rhs )
        : myData(rhs.myData)
    {
    }

    mstring::iterator mstring::begin () const
    {
        return (iterator(myData.c_str()));
    }

    mstring::iterator mstring::end () const
    {
        iterator position = begin();
        while ( **position != L'\0' ) {
            ++position;
        }
        return (position);
    }

    void mstring::swap ( mstring& rhs )
    {
        myData.swap(rhs.myData);
    }

    mstring& mstring::operator= ( const mstring& rhs )
    {
        mstring copy(rhs);
        copy.swap(*this);
        return (*this);
    }

    void swap ( mstring& lhs, mstring& rhs )
    {
        lhs.swap(rhs);
    }

    mstring::iterator::iterator ( const wchar_t * position )
        : myPosition(position)
    {
    }

    const wchar_t * mstring::iterator::operator* () const
    {
        return (myPosition);
    }

    mstring::iterator& mstring::iterator::operator++ ()
    {
        for ( ++myPosition; (*myPosition++ != L'\0'); )
            ;
        return (*this);
    }

    mstring::iterator mstring::iterator::operator++ ( int )
    {
        iterator old(*this);
        ++(*this);
        return (old);
    }

    bool mstring::iterator::operator== ( const iterator& other ) const
    {
        return (myPosition == other.myPosition);
    }

    bool mstring::iterator::operator!= ( const iterator& other ) const
    {
        return (myPosition != other.myPosition);
    }

}
