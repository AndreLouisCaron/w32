#ifndef _w32_msi_Products_hpp__
#define _w32_msi_Products_hpp__

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

#include "__configure__.hpp"
#include <w32.msi/Product.hpp>

namespace w32 { namespace msi {

    /*!
     * @ingroup w32-msi
     * @brief
     */
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
