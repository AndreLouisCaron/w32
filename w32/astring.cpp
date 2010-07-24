// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/astring.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>
#include <iostream>
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
        ::memcpy(result,value,sizeof(T)*size);
        return (result);
    }

        // Request the number of characters to allocate.
    ::DWORD count ( ::UINT codepage, ::LPCWSTR value )
    {
        const int result = ::WideCharToMultiByte(
            codepage, 0, value, -1, 0, 0, 0, 0
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(WideCharToMultiByte,error);
        }
        return (result);
    }

        // Codepage is target encoding.
    ::LPSTR encode ( ::UINT codepage, ::DWORD size, ::LPCWSTR value )
    {
        char *const data = allocate<char>(size);
        const int result = ::WideCharToMultiByte(
            codepage, 0, value, -1, data, size, 0, 0
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_INSUFFICIENT_BUFFER )
            {
            }
            UNCHECKED_WIN32C_ERROR(WideCharToMultiByte,error);
        }
        return (data);
    }

}

namespace w32 {

    astring::astring ()
        : mySize(0),
          myData(::duplicate(mySize, "")),
          myEncoding(Codepage::ansi())
    {
    }

    astring::astring ( const char_type * other, Codepage encoding )
        : mySize(count(other)),
          myData(::duplicate(mySize, other)),
          myEncoding(encoding)
    {
    }

    astring::astring ( const std::string& other, Codepage encoding )
        : mySize(other.size()),
          myData(::duplicate(mySize, other.c_str())),
          myEncoding(encoding)
    {
    }

    astring::astring ( const wchar_t * other, Codepage encoding )
        : mySize(::count(encoding, other)),
          myData(::encode(encoding, mySize, other)),
          myEncoding(encoding)
    {
    }

    astring::astring ( const std::wstring& other, Codepage encoding )
        : mySize(::count(encoding, other.c_str())),
          myData(::encode(encoding, mySize, other.c_str())),
          myEncoding(encoding)
    {
    }

    astring::astring ( const string& other, Codepage encoding )
        : mySize(::count(encoding, other.data())),
          myData(::encode(encoding, mySize, other.data())),
          myEncoding(encoding)
    {
    }

    astring::astring ( const box& value )
        : mySize(value.size()),
          myData(value.data()),
          myEncoding(value.encoding())
    {
    }

    astring::astring ( const astring& other )
        : mySize(other.size()),
          myData(::duplicate(mySize, other.data())),
          myEncoding(other.encoding())
    {
    }

    astring::~astring ()
    {
        mySize = 0;
        delete [] myData;
        myData = 0;
    }

    dword astring::size () const
    {
        return (mySize);
    }

    dword astring::length () const
    {
        return (mySize);
    }

    bool astring::empty () const
    {
        return (size() == 0);
    }

    const char * astring::data () const
    {
        return (myData);
    }

    const char * astring::c_str () const
    {
        return (myData);
    }

    char * astring::data ()
    {
        return (myData);
    }

    char * astring::c_str ()
    {
        return (myData);
    }

    const Codepage astring::encoding () const
    {
        return (myEncoding);
    }

    astring::iterator astring::begin ()
    {
        return (data());
    }

    astring::iterator astring::end ()
    {
        return (data() + size());
    }

    astring::const_iterator astring::begin () const
    {
        return (data());
    }

    astring::const_iterator astring::end () const
    {
        return (data() + size());
    }

    void astring::swap ( astring& other )
    {
        std::swap(mySize,other.mySize);
        std::swap(myData,other.myData);
        std::swap(myEncoding,other.myEncoding);
    }

    astring& astring::operator= ( const astring& other )
    {
        astring copy(other);
        copy.swap(*this);
        return (*this);
    }

    astring& astring::operator= ( const char * other )
    {
        astring copy(other);
        copy.swap(*this);
        return (*this);
    }

    astring& astring::operator= ( const std::string& other )
    {
        astring copy(other);
        copy.swap(*this);
        return (*this);
    }

    std::ostream& operator<< ( std::ostream& out, const astring& value )
    {
        return (out << value.data());
    }

    astring::box::box ( char_type * data, Codepage encoding )
        : mySize(std::strlen(data)), myData(data), myEncoding(encoding)
    {
    }

    astring::box::box ( char_type * data, dword size, Codepage encoding )
        : mySize(size), myData(data), myEncoding(encoding)
    {
    }

    const dword astring::box::size () const
    {
        return (mySize);
    }

    char *const astring::box::data () const
    {
        return (myData);
    }

    const Codepage astring::box::encoding () const
    {
        return (myEncoding);
    }

}
