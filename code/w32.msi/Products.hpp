#ifndef _w32_msi_Products_hpp__
#define _w32_msi_Products_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.msi/Product.hpp>

namespace w32 { namespace msi {

    class Products
    {
        /* nested types. */
    public:
        class Context; class User;

        /* data. */
    private:
        dword myIndex;
        const wchar_t * myUser;
        dword myContext;
        wchar_t myProduct[38+1];

        /* construction. */
    public:
            /*!
             * @brief Lists all installed products for the machine.
             */
        Products ();

            /*!
             * @brief Lists all installed products for a user.
             */
        Products ( const User& user, const Context& context );

        /* methods. */
    public:
        bool next ();

            /*!
             * @brief Gets the product code for the current product.
             */
        Product::Code current () const;
    };

    class Products::User
    {
        /* nested types. */
    public:
        typedef const wchar_t * Value;

        /* class data. */
    public:
        static const User current ();
        static const User all ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        User ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

    class Products::Context
    {
        /* nested types. */
    public:
        typedef dword Value;

        /* class data. */
    public:
        static const Context machine ();
        static const Context managed ();
        static const Context unmanaged ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Context ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

} }

#endif /* _w32_msi_Products_hpp__ */
