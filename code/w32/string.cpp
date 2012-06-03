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

#include <w32/string.hpp>
#include <w32/astring.hpp>
#include <w32/Error.hpp>
#include <algorithm>
#include <iostream>
#include <limits>
#include <cstring>

namespace {

        // Allocate a string and automatically terminate it.
    template<typename T>
    T * allocate ( ::DWORD size )
    {
        T *const result = new T[size+1];
        result[size] = T(0);
        return (result);
    }

        // Returns the number of characters to allocate.
    template<typename T>
    ::DWORD count ( const T * value )
    {
        if ( value == 0 ) {
            return (0);
        }
        static const T terminator(0);
        ::DWORD result = 0;
        for ( ; (*value != terminator); ++value ) {
            ++result;
        }
        return (result);
    }

        // Allocate a fresh copy of a string.
    template<typename T>
    T * duplicate ( ::DWORD size, const T * value )
    {
        T *const result = allocate<T>(size);
        ::memcpy(result, value, sizeof(T)*size);
        return (result);
    }

        // Request the number of characters to allocate.
    ::DWORD count ( ::UINT codepage, const char * value )
    {
        const int result = ::MultiByteToWideChar
            (codepage, 0, value, -1, 0, 0);
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(MultiByteToWideChar,error);
        }
        return (result);
    }

        // Codepage is source encoding!
    ::WCHAR * decode ( ::UINT codepage, ::DWORD& size, const char * value )
    {
        ::WCHAR *const data = allocate<::WCHAR>(size);
        const int result = ::MultiByteToWideChar
            (codepage, 0, value, -1, data, size+1);
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(MultiByteToWideChar,error);
        }
        // The decoded string doesn't forcibly have the same number of code
        // points as the encoded string.  For example, in UTf-8, "LATIN SMALL
        // LETTER E WITH ACUTE" is encoded as (0xC3, 0xA9) by is encoded as a
        // single (0x00e9) in UTF-16, effecively reducing the string length by
        // 1 codepoint.  Keep the freshly computed string length :-)
        size = result-1; // (don't count trailing terminator).
        return (data);
    }

}

namespace w32 {

    const string::size_type string::npos =
        std::numeric_limits< string::size_type >::max();

    string::string ()
        : mySize(0),
          myData(::duplicate(mySize, L""))
    {
    }

    string::string ( const char * other, Codepage encoding )
        : mySize(::count(other)),
          myData(::decode(encoding, mySize, other))
    {
    }

    string::string ( const char * other, size_type size, Codepage encoding )
        : mySize(size),
          myData(::decode(encoding, mySize, other))
    {
    }

    string::string ( const astring& other )
        : mySize(other.size()),
          myData(decode(other.encoding(), mySize, other.data()))
    {
    }

    string::string ( const std::string& other, Codepage encoding )
        : mySize(other.size()),
          myData(::decode(encoding, mySize, other.data()))
    {
    }

    string::string ( const_pointer other )
        : mySize(count(other)),
          myData(duplicate(mySize,other))
    {
    }

    string::string ( const_pointer other, size_type size )
        : mySize(size),
          myData(duplicate(mySize,other))
    {
    }
    string::string ( const box& value )
        : mySize(value.size()),
          myData(value.data())
    {
    }

    string::string ( size_type size, char_type filler )
        : mySize(size),
          myData(::allocate<wchar_t>(size))
    {
        std::fill(begin(), end(), filler);
    }

    string::string ( const string& other )
        : mySize(other.size()),
          myData(duplicate(mySize,other.data()))
    {
    }

    string::~string ()
    {
        delete [] myData;
        myData = 0;
        mySize = 0;
    }

    string::size_type string::size() const
    {
        return (mySize);
    }

    string::size_type string::length() const
    {
        return (mySize);
    }

    bool string::empty () const
    {
        return (size() == 0);
    }

    string::pointer string::data ()
    {
        return (myData);
    }

    string::const_pointer string::data () const
    {
        return (myData);
    }

    string::pointer string::c_str ()
    {
        return (myData);
    }

    string::const_pointer string::c_str () const
    {
        return (myData);
    }

    void string::erase ( iterator begin, iterator end )
    {
            // Copy trailing characters.
        end = std::copy(end, myData+mySize, begin);

            // Terminate string.
        myData[mySize = (end-myData)] = L'\0';
    }

    void string::resize ( size_type length, wchar_t filler )
    {
            // Don't reallocate when not required to.
        if ( length <= size() ) {
            erase(begin()+size(), end());
        }
        else {
            string other(length, filler);
            std::copy(begin(), end(), other.begin());
            swap(other);
        }
    }

    void string::clear ()
    {
        erase(begin(), end());
    }

    string string::substr ( size_type offset, size_type length ) const
    {
        offset = std::min(offset,        size());
        length = std::min(offset+length, size());
        return (string(data()+offset, length));
    }

    string::iterator string::begin ()
    {
        return (data());
    }

    string::iterator string::end ()
    {
        return (data() + size());
    }

    string::const_iterator string::begin () const
    {
        return (data());
    }

    string::const_iterator string::end () const
    {
        return (data() + size());
    }

    void string::swap ( string& other )
    {
        std::swap(mySize,other.mySize);
        std::swap(myData,other.myData);
    }

    string& string::operator= ( const string& other )
    {
        string copy(other);
        copy.swap(*this);
        return (*this);
    }

    string& string::operator= ( const_pointer other )
    {
        string copy(other);
        copy.swap(*this);
        return (*this);
    }

    string& string::operator= ( const std::wstring& other )
    {
        string copy(other.c_str());
        copy.swap(*this);
        return (*this);
    }

    bool string::operator== ( const string& rhs ) const
    {
        return (std::wcscmp(data(), rhs.data()) == 0);
    }

    bool string::operator!= ( const string& rhs ) const
    {
        return (std::wcscmp(data(), rhs.data()) != 0);
    }

    bool string::operator< ( const string& rhs ) const
    {
        return (std::wcscmp(data(), rhs.data()) < 0);
    }

    bool string::operator<= ( const string& rhs ) const
    {
        return (std::wcscmp(data(), rhs.data()) <= 0);
    }

    bool string::operator> ( const string& rhs ) const
    {
        return (std::wcscmp(data(), rhs.data()) > 0);
    }

    bool string::operator>= ( const string& rhs ) const
    {
        return (std::wcscmp(data(), rhs.data()) >= 0);
    }

    string& string::operator+= ( const string& rhs )
    {
        if ( length() == 0 ) {
            return ((*this) = rhs);
        }
        string result(length() + rhs.length());
        std::copy(rhs.begin(), rhs.end(),
                  std::copy(begin(), end(), result.begin()));
        result.swap(*this);
        return (*this);
    }

    string string::operator+ ( const string& rhs ) const
    {
        string result(*this);
        result += rhs;
        return (result);
    }

    string& string::operator+= ( wchar_t rhs )
    {
        resize(1+size());
        (*this)[size()-1] = rhs;
        return (*this);
    }

    string string::operator+ ( wchar_t rhs ) const
    {
        string result(*this);
        result += rhs;
        return (result);
    }

    string operator+ ( const wchar_t * lhs, const string& rhs )
    {
        return (string(lhs) + rhs);
    }

    std::wostream& operator<< ( std::wostream& out, const string& value )
    {
        return (out << value.data());
    }

    string::box::box ( pointer data )
        : mySize(std::wcslen(data)), myData(data)
    {
    }

    string::box::box ( pointer data, size_type size )
        : mySize(size), myData(data)
    {
    }

    string::size_type string::box::size() const
    {
        return (mySize);
    }

    string::pointer string::box::data () const
    {
        return (myData);
    }

}
