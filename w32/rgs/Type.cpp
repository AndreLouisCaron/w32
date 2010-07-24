// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/rgs/Type.hpp>
#include <w32/rgs/Value.hpp>
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
