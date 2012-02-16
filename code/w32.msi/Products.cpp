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

#include <w32.msi/Products.hpp>
#include <w32.msi/Error.hpp>
#include <w32/Error.hpp>

namespace {

    bool enumerate
        ( ::LPCWSTR user, ::DWORD context, ::DWORD& index, ::LPWSTR product )
    {
        product[38] = L'\0';
        const ::UINT result = ::MsiEnumProductsExW(
            0, user, context, index, product, 0, 0, 0
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_NO_MORE_ITEMS ) {
                return (false);
            }
            if ( result == ERROR_ACCESS_DENIED ) {
            }
            if ( result == ERROR_BAD_CONFIGURATION ) {
            }
            if ( result == ERROR_INVALID_PARAMETER ) {
            }
            if ( result == ERROR_MORE_DATA ) {
            }
            if ( result == ERROR_UNKNOWN_PRODUCT ) {
            }
            if ( result == ERROR_FUNCTION_FAILED ) {
            }
            UNCHECKED_INSTALLER_ERROR(MsiEnumProductsEx,result);
        }
        ++index; return (true);
    }

}

namespace w32 { namespace msi {

    const Products::User Products::User::current ()
    {
        return (0);
    }

    const Products::User Products::User::all ()
    {
        return (L"s-1-1-0");
    }

    Products::User::User ( Value value )
        : myValue(value)
    {
    }

    Products::User::Value Products::User::value () const
    {
        return (myValue);
    }

    Products::User::operator Products::User::Value () const
    {
        return (myValue);
    }

    const Products::Context Products::Context::machine ()
    {
        return (MSIINSTALLCONTEXT_MACHINE);
    }

    const Products::Context Products::Context::managed ()
    {
        return (MSIINSTALLCONTEXT_USERMANAGED);
    }

    const Products::Context Products::Context::unmanaged ()
    {
        return (MSIINSTALLCONTEXT_USERUNMANAGED);
    }

    Products::Context::Context ( Value value )
        : myValue(value)
    {
    }

    Products::Context::Value Products::Context::value () const
    {
        return (myValue);
    }

    Products::Context::operator Products::Context::Value () const
    {
        return (myValue);
    }

    Products::Products ()
        : myIndex(0), myUser(0), myContext(Context::machine())
    {
    }

    Products::Products ( const User& user, const Context& context )
        : myIndex(0), myUser(user.value()), myContext(context.value())
    {
    }

    bool Products::next ()
    {
        return (::enumerate(myUser, myContext, myIndex, myProduct));
    }

    Product::Code Products::current () const
    {
        return (Product::Code(myProduct));
    }

} }
