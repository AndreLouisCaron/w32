// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/rgs/Value.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace rgs {

    Value::Value ( const Key& key, const string& name )
        : myKey(key), myName(name)
    {
    }

    Value::Value ( const Key& key, const string& name, const string& value )
        : myKey(key), myName(name)
    {
        (*this) = value;
    }

    const Key& Value::key () const
    {
        return (myKey);
    }

    const string& Value::name () const
    {
        return (myName);
    }

    Type Value::type () const
    {
        return (Type::of(*this));
    }

    Value& Value::operator= ( const string& value )
    {
        const ::LONG result = ::RegSetValueExW(
            myKey.handle(), myName.data(), 0, REG_SZ,
            (::LPCBYTE)value.data(), ::DWORD(value.length()+1)*sizeof(::WCHAR)
            );
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegSetValueEx,result);
        }
        return (*this);
    }

    Value::operator const string () const
    {
        ::DWORD type = REG_SZ;
        
            // Query the length of the string.
        ::BYTE dummy = 0;
        ::DWORD length = 1;
        ::LONG result = ::RegQueryValueExW(
            myKey.handle(), myName.data(), 0, &type, &dummy, &length
            );
        if ( result != ERROR_MORE_DATA ) {
            UNCHECKED_WIN32C_ERROR(RegQueryValueEx,result);
        }
        
            // Query the value.
        string value(length/sizeof(::WCHAR));
        result = ::RegQueryValueExW(
            myKey.handle(), myName.data(), 0, &type,
            (::LPBYTE)value.data(), &length
            );
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegQueryValueEx,result);
        }
        return (value);
    }

    Value& Value::operator= ( const ::DWORD& data )
    {
        const ::LONG result = ::RegSetValueExW(
            myKey.handle(), myName.data(), 0, REG_DWORD,
            (::LPCBYTE)&data, ::DWORD(sizeof(::DWORD))
            );
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegSetValueEx,result);
        }
        return (*this);
    }

} }
