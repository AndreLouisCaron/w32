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

#include <w32.msi/Product.hpp>
#include <w32.msi/Error.hpp>

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
