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

#include <w32/bstring.hpp>
#include <w32/string.hpp>
#include <algorithm>
#include <memory>
#include <ostream>

namespace {

    ::BSTR duplicate ( const ::WCHAR * contents )
    {
        const ::BSTR value = ::SysAllocString(contents);
        if ( value == 0 ) {
            throw (std::bad_alloc());
        }
        return (value);
    }

    ::BSTR duplicate ( const ::WCHAR * contents, ::UINT length )
    {
        const ::BSTR value = ::SysAllocStringLen(contents, length);
        if ( value == 0 ) {
            throw (std::bad_alloc());
        }
        return (value);
    }

    ::BSTR duplicate ( ::BSTR contents )
    {
        const ::BSTR value = ::SysAllocString(contents);
        if ( value == 0 ) {
            throw (std::bad_alloc());
        }
        return (value);
    }

}

namespace w32 {

    bstring::bstring ()
        : myValue(::duplicate(L""))
    {
    }

    bstring::bstring ( value_type contents )
        : myValue(::duplicate(contents))
    {
    }

    bstring::bstring ( const_pointer contents )
        : myValue(::duplicate(contents))
    {
    }

    bstring::bstring ( const_pointer contents, size_type size )
        : myValue(::duplicate(contents))
    {
    }

    bstring::bstring ( const string& contents )
        : myValue(duplicate(contents.c_str()))
    {
    }

    bstring::bstring ( const box& contents )
        : myValue(contents.value())
    {
    }

    bstring::bstring ( const bstring& other )
        : myValue(::duplicate(other.data()))
    {
    }

    bstring::~bstring ()
    {
        ::SysFreeString(myValue);
    }

    bstring::value_type bstring::value () const
    {
        return (myValue);
    }

    bstring::const_pointer bstring::data () const
    {
        return (myValue);
    }

    bstring::size_type bstring::size () const
    {
        return (::SysStringLen(myValue));
    }

    bstring::size_type bstring::length () const
    {
        return (::SysStringLen(myValue));
    }

    void bstring::swap ( bstring& rhs )
    {
        std::swap(myValue, rhs.myValue);
    }

    bool bstring::empty () const
    {
        return (size() == 0);
    }

    bstring::const_iterator bstring::begin () const
    {
        return (data());
    }

    bstring::const_iterator bstring::end () const
    {
        return (begin() + size());
    }

    bstring& bstring::operator= ( const bstring& other )
    {
        bstring clone(other);
        clone.swap(*this);
        return (*this);
    }

    bstring& bstring::operator= ( const_pointer contents )
    {
        bstring clone(contents);
        clone.swap(*this);
        return (*this);
    }

    bstring& bstring::operator= ( const string& contents )
    {
        bstring clone(contents);
        clone.swap(*this);
        return (*this);
    }

    bstring::operator string() const
    {
        return (string(myValue));
    }

    bstring::operator std::wstring() const
    {
        return (std::wstring(myValue));
    }

    bool bstring::operator== ( const bstring& rhs ) const
    {
        return (std::wcscmp(data(), rhs.data()) == 0);
    }

    bool bstring::operator!= ( const bstring& rhs ) const
    {
        return (std::wcscmp(data(), rhs.data()) != 0);
    }

    std::wostream& operator<< ( std::wostream& out, const bstring& value )
    {
        return (out << value.data());
    }

    bstring::box::box ( value_type value )
        : myValue(value)
    {
    }

    bstring::value_type bstring::box::value () const
    {
        return (myValue);
    }

}
