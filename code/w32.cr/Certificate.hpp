#ifndef _w32_cr_Certificate_hpp__
#define _w32_cr_Certificate_hpp__

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

/*!
 * @file w32.cr/Certificate.hpp
 * @brief Cryptographic certificate for reliable identification.
 */

#include "__configure__.hpp"
#include <w32/Reference.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace cr {

    class Blob;
    class Provider;

    //! @addtogroup w32-cr
    //! @{

    /*!
     * @brief Cryptographic certificate reliable identification.
     */
    class Certificate
    {
        /* nested types. */
    public:
        /*!
         * @brief Native handle for the certificate object.
         *
         * @see claim()
         * @see proxy()
         */
        typedef Reference< ::PCCERT_CONTEXT > Handle;

        class Encoding;

        /* class methods. */
    public:
        /*!
         * @brief Manage an existing certificate's handle.
         * @param object Native handle for an existing certificate object.
         * @return A wrapper object for the object handle.
         *
         * This function creates a handle that will @e always release the
         * handle when the last reference goes out of scope.  If the object's
         * lifetime is already managed by another construct and you only need
         * to wrap the object for compatibility purposes, use the proxy()
         * function instead.
         *
         * @see Handle
         * @see proxy()
         */
        static const Handle claim ( ::PCCERT_CONTEXT object );

        /*!
         * @brief Proxy an existing certificate's handle.
         * @param object Native handle for an existing certificate object.
         * @return A wrapper object for the object handle.
         *
         * This function creates a handle that will @c never release the handle
         * even after the last reference goes out of scope.  If you want a
         * @c Certificate instance to manage the object's lifetime for you, use
         * the @c claim() function instead.
         *
         * @see Handle
         * @see claim()
         */
        static const Handle proxy ( ::PCCERT_CONTEXT object );

        /*!
         * @brief Create a self-signed certificate using the default provider.
         * @param provider The cryptographic provider.
         * @param subject Object identifier (OID) or X.500 name.
         *
         * @note If the provider is opened with the @c newKeySet() hint, 
         *
         * @see Provider::Hints::newKeySet()
         */
        static Certificate self_signed ( Provider& provider, string subject );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        /*!
         * @brief Create a certificate object from an existing certificate.
         * @param handle The certificate object handle.
         *
         * @see Handle
         * @see claim()
         * @see proxy()
         */
        explicit Certificate ( const Handle& handle );

        /*!
         * @brief Deserialize a certificate encoded using @a encoding.
         * @param blob Encoded certificate.
         * @param encoding Encoding used to encode the certificate.
         */
        Certificate ( const Blob& blob, const Encoding& encoding );

        /* methods. */
    public:
        /*!
         * @brief Access the certificate object's native handle.
         * @return The certificate object handle.
         */
        const Handle& handle () const;

        /*!
         * @brief Checks that the certificate has not yet expired.
         * @return @c false if the certificate is expired, else @c true.
         *
         * @note This function does not check a certification revocation list.
         */
        bool valid () const;
    };

    /*!
     * @brief Enumeration fo certificate encodings used for storage.
     */
    class Certificate::Encoding
    {
        /* nested types. */
    public:
        /*!
         * @brief Native encoding type code.
         */
        typedef ::DWORD Value;

        /* class methods. */
    public:
        /*!
         * @brief Used for signing and encryption of messages.
         *
         * @see http://en.wikipedia.org/wiki/PKCS
         * @see http://tools.ietf.org/html/rfc2315
         */
        static const Encoding pkcs7 ();

        /*!
         * @brief Use for PKI and PMI.
         *
         * @see http://en.wikipedia.org/wiki/X.509
         */
        static const Encoding x509 ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        // For internal use only.
        Encoding ( Value value );

        /* operators. */
    public:
        /*!
         * @brief Obtain the native encoding type code.
         */
        operator Value () const;
    };

    //! @}

} }

#endif /* _w32_cr_Certificate_hpp__ */
