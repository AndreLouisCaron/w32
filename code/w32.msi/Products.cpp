// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
