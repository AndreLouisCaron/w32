// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <com/Guid.hpp>
#include <w32/string.hpp>
#include <iostream>
#include <string>

namespace {

    static const ::GUID Zero = { 0 };

}

namespace w32{ namespace com {

    const Guid Guid::zero ()
    {
        return (Guid(Zero));
    }

    Guid::Guid (
        dword a, word b, word c,
        byte d, byte e, byte f, byte g,
        byte h, byte i, byte j, byte k
        )
    {
        const ::GUID value = {
            a, b, c, { d, e, f, g, h, i, j, k }
        };
        myValue = value;
    }

    Guid::Guid ( const Guid& other )
        : myValue(other.myValue)
    {
    }

    Guid::Guid ( const Value& value )
        : myValue(value)
    {
    }

    Guid::Value& Guid::value ()
    {
        return (myValue);
    }

    const Guid::Value& Guid::value () const
    {
        return (myValue);
    }

    Guid& Guid::operator= ( const Guid& other )
    {
        myValue = other.myValue;
        return (*this);
    }

    Guid::operator const Guid::Value& () const
    {
        return (myValue);
    }

    bool Guid::operator== ( const Guid& other ) const
    {
        return (::IsEqualGUID(myValue,other.myValue) == TRUE);
    }

    bool Guid::operator!= ( const Guid& other ) const
    {
        return (::IsEqualGUID(myValue,other.myValue) == FALSE);
    }

    std::wostream& operator<< ( std::wostream& out, const Guid& guid )
    {
        return (out << Guid::String(guid).value());
    }

    std::wistream& operator>> ( std::wistream& in, Guid& guid )
    {
        string value;
        if ( !getline(in, value, L'}') ) {
            in.setstate(std::wios::failbit); return (in);
        }
        value += L'}';
        const ::HRESULT result =
            ::CLSIDFromString(value.c_str(), &guid.value());
        if ( result == CO_E_CLASSSTRING ) {
            in.setstate(std::wios::failbit); return (in);
        }
        return (in);
    }

    Guid::String::String ( const Guid& guid )
    {
        ::StringFromGUID2(guid.value(), myValue, 39);
    }

    const wchar_t * Guid::String::value () const
    {
        return (myValue);
    }

    std::wostream& operator<< ( std::wostream& out, const Guid::String& guid )
    {
        return (out << guid.value());
    }

} }
