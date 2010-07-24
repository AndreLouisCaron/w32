// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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

    Variant::operator bstring() const
    {
            // Extract directly if of proper type.
        if ( type() == Type::string() ) {
            return (value().bstrVal);
        }
            // Coerce if required.
        return (Variant(*this, Type::string()).value().bstrVal);
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
