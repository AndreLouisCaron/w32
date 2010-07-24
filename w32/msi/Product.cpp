// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/msi/Product.hpp>
#include <w32/msi/Error.hpp>

namespace {

    ::DWORD length ( const wchar_t * product, const wchar_t * property )
    {
        wchar_t value[] = L"";
        ::DWORD count = 0;
        const ::UINT result = ::MsiGetProductInfoW(
            product, property, value, &count
            );
        if ((result != ERROR_SUCCESS) && (result != ERROR_MORE_DATA)) {
            UNCHECKED_INSTALLER_ERROR(MsiGetProductInfo,result);
        }
        return (count);
    }

    void fetch ( const wchar_t * product, const wchar_t * property,
                 wchar_t * value, ::DWORD count )
    {
        const ::UINT result = ::MsiGetProductInfoW(
            product, property, value, &++count
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_BAD_CONFIGURATION ) {
            }
            if ( result == ERROR_INVALID_PARAMETER ) {
            }
            if ( result == ERROR_MORE_DATA ) {
            }
            if ( result == ERROR_UNKNOWN_PRODUCT ) {
            }
            if ( result == ERROR_UNKNOWN_PROPERTY ) {
            }
            UNCHECKED_INSTALLER_ERROR(MsiGetProductInfo,result);
        }
    }

}

#include <iostream>

namespace w32 { namespace msi {

    Product::Product ( const Code& code )
        : myCode(code)
    {
    }

    const Product::Code& Product::code () const
    {
        return (myCode);
    }

    string Product::operator() ( const string& identifier ) const
    {
        const string code = myCode.value();
        const ::DWORD count = length(code.data(),identifier.data());
        string value(count);
        fetch(code.data(), identifier.data(), value.data(), count);
        return (value);
    }

} }
