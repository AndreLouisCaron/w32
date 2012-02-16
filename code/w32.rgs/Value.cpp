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

#include <w32.rgs/Value.hpp>
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
