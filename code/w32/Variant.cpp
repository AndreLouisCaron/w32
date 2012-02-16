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

#include <w32/Variant.hpp>
#include <w32/Error.hpp>

// TODO: make sure that HRESULTs are WIN32C error codes.

namespace {

    void morph ( ::VARIANT& variant, ::VARTYPE type )
    {
        const ::HRESULT result = ::VariantClear(&variant);
        if ( result != S_OK ) {
            UNCHECKED_WIN32C_ERROR(VariantClear, result);
        }
        variant.vt = type;
    }

}

namespace w32 {

    Variant::Variant ()
    {
        ::VariantInit(&myValue);
    }

    Variant::Variant ( const Value& value )
    {
        ::VariantInit(&myValue);
        const ::HRESULT result = ::VariantCopy(&myValue,&value);
        if ( result != S_OK ) {
            UNCHECKED_WIN32C_ERROR(VariantCopy, result);
        }
    }

    Variant::Variant ( const Variant& other )
    {
        ::VariantInit(&myValue);
        (*this) = other;
    }

    Variant::Variant ( const Variant& other, const Type& type )
    {
        ::VariantInit(&myValue);
        (*this) = other;
        coerce(type);
    }

    Variant::~Variant ()
    {
        clear();
    }

    Variant::Value& Variant::value ()
    {
        return (myValue);
    }

    const Variant::Value& Variant::value () const
    {
        return (myValue);
    }

    void Variant::clear ()
    {
        const ::HRESULT result = ::VariantClear(&value());
        if ( result != S_OK ) {
            UNCHECKED_WIN32C_ERROR(VariantClear,result);
        }
    }

    void Variant::coerce ( const Type& type )
    {
        static const ::WORD flags = 0;
        const ::HRESULT result = ::VariantChangeType(
            &value(), &value(), flags, type.value()
            );
        if ( result != S_OK ) {
            UNCHECKED_WIN32C_ERROR(VariantChangeType,result);
        }
    }

    Variant::Type Variant::type () const
    {
        return (Type::of(*this));
    }

    Variant& Variant::operator= ( const Variant& rhs )
    {
        clear();
        const ::HRESULT result = ::VariantCopy(&myValue,&rhs.myValue);
        if ( result != S_OK ) {
            UNCHECKED_WIN32C_ERROR(VariantCopy, result);
        }
        return (*this);
    }

    Variant& Variant::operator= ( bool value )
    {
        if ( type() != Type::boolean() ) {
            morph(myValue, Type::boolean());
        }
        this->value().boolVal = (value == true)? TRUE : FALSE;
        return (*this);
    }

    Variant& Variant::operator= ( int value )
    {
        if ( type() != Type::integer() ) {
            morph(myValue, Type::integer());
        }
        this->value().lVal = value;
        return (*this);
    }

    Variant& Variant::operator= ( const bstring& string )
    {
        if ( type() != Type::string() ) {
            morph(myValue, Type::string());
        }
        this->value().bstrVal = ::SysAllocString(string.data());
        return (*this);
    }

    Variant& Variant::operator= ( ::BSTR string )
    {
        if ( type() != Type::string() ) {
            morph(myValue, Type::string());
        }
        this->value().bstrVal = ::SysAllocString(string);
        return (*this);
    }

    Variant& Variant::operator= ( const astring& value )
    {
        if ( type() != Type::string() ) {
            morph(myValue, Type::string());
        }
        this->value().bstrVal = ::SysAllocString(string(value).data());
        return (*this);
    }

    Variant& Variant::operator= ( const string& value )
    {
        if ( type() != Type::string() ) {
            morph(myValue, Type::string());
        }
        this->value().bstrVal = ::SysAllocString(value.data());
        return (*this);
    }

    Variant& Variant::operator= ( const std::string& value )
    {
        if ( type() != Type::string() ) {
            morph(myValue, Type::string());
        }
        this->value().bstrVal = ::SysAllocString(
            string(value, Codepage::ansi()).data());
        return (*this);
    }

    Variant& Variant::operator= ( const std::wstring& value )
    {
        if ( type() != Type::string() ) {
            morph(myValue, Type::string());
        }
        this->value().bstrVal = ::SysAllocString(value.data());
        return (*this);
    }

    Variant& Variant::operator= ( ::IUnknown * value )
    {
        if ( type() != Type::iunknown() ) {
            morph(myValue, Type::iunknown());
        }
        this->value().punkVal = value;
        return (*this);
    }

    Variant::operator bstring () const
    {
            // Extract directly if of proper type.
        if ( type() == Type::string() ) {
            return (value().bstrVal);
        }
            // Coerce if required.
        return (Variant(*this, Type::string()).value().bstrVal);
    }

    Variant::operator int32 () const
    {
            // Extract directly if of proper type.
        if ( type() == Type::integer() ) {
            return (value().lVal);
        }
            // Coerce if required.
        return (Variant(*this, Type::integer()).value().lVal);
    }

    const Variant::Type Variant::Type::empty ()
    {
        return (VT_EMPTY);
    }

    const Variant::Type Variant::Type::null ()
    {
        return (VT_NULL);
    }

    const Variant::Type Variant::Type::boolean ()
    {
        return (VT_BOOL);
    }

    const Variant::Type Variant::Type::integer ()
    {
        return (VT_INT);
    }

    const Variant::Type Variant::Type::result ()
    {
        return (VT_HRESULT);
    }

    /*const Variant::Type Variant::Type::bstring ()
    {
        return (VT_BSTR);
    }

    const Variant::Type Variant::Type::astring ()
    {
        return (VT_LPSTR);
    }*/

    const Variant::Type Variant::Type::string ()
    {
        //return (VT_LPWSTR);
        return (VT_BSTR);
    }

    const Variant::Type Variant::Type::iunknown ()
    {
        return (VT_UNKNOWN);
    }

    Variant::Type Variant::Type::of ( const Variant& variant )
    {
        return (Type(variant.value().vt));
    }

    Variant::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Variant::Type::Value Variant::Type::value () const
    {
        return (myValue);
    }

    Variant::Type::operator Value () const
    {
        return (myValue);
    }

    bool Variant::Type::operator== ( const Type& other ) const
    {
        return (myValue == other.myValue);
    }

    bool Variant::Type::operator!= ( const Type& other ) const
    {
        return (myValue != other.myValue);
    }

}
