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

#include <w32.rgs/Type.hpp>
#include <w32.rgs/Value.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace rgs {

    const Type Type::none ()
    {
        return (REG_NONE);
    }

    const Type Type::string ()
    {
        return (REG_SZ);
    }

    const Type Type::dword ()
    {
        return (REG_DWORD);
    }

    const Type Type::binary ()
    {
        return (REG_BINARY);
    }

    const Type Type::unexpanded ()
    {
        return (REG_EXPAND_SZ);
    }

    const Type Type::multistring ()
    {
        return (REG_MULTI_SZ);
    }

    const Type Type::of ( const rgs::Value& value )
    {
        ::DWORD type = REG_NONE;
        const ::DWORD result = ::RegQueryValueExW(
            value.key().handle(), value.name().data(), 0, &type, 0, 0
            );
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegQueryValueEx,result);
        }
        return (Type(type));
    }

    Type::Type ( Value value )
        : myValue(value)
    {
    }

    Type::Value Type::value () const
    {
        return (myValue);
    }

    bool Type::operator== ( const Type& other ) const
    {
        return (myValue == other.myValue);
    }

    bool Type::operator!= ( const Type& other ) const
    {
        return (!this->operator==(other));
    }

    Type::operator Type::Value () const
    {
        return (myValue);
    }

} }
