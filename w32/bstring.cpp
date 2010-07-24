// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
