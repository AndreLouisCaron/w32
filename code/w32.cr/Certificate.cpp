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
 * @file w32.cr/Certificate.cpp
 * @brief Cryptographic certificate reliable identification.
 */

#include <w32.cr/Certificate.hpp>
#include <w32.cr/Blob.hpp>
#include <w32.cr/Key.hpp>
#include <w32.cr/Provider.hpp>
#include <w32/Delta.hpp>
#include <w32/Error.hpp>
#include <w32/Time.hpp>
#include <w32/string.hpp>

namespace {

    ::PCCERT_CONTEXT acquire
        ( const ::BYTE * data, ::DWORD size, ::DWORD encoding )
    {
        const ::PCCERT_CONTEXT handle =
            ::CertCreateCertificateContext(encoding, data, size);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertCreateCertificateContext, error);
        }
        return (handle);
    }

    void abandon ( ::PCCERT_CONTEXT object ) {}
    void release ( ::PCCERT_CONTEXT object )
    {
        const ::BOOL result = ::CertFreeCertificateContext(object);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertFreeCertificateContext, error);
        }
    }

}

namespace w32 { namespace cr {

    const Certificate::Handle Certificate::claim ( ::PCCERT_CONTEXT object )
    {
        return (Handle(object, &::release));
    }

    const Certificate::Handle Certificate::proxy ( ::PCCERT_CONTEXT object )
    {
        return (Handle(object, &::abandon));
    }

    Certificate Certificate::self_signed ( Provider& provider, string subject )
    {
        // Generate a new exportable exchange key.
        const Key::Type key_type = Key::Type::exchange();
        Key key = Key::generate
            (provider, key_type, Key::Hints().exportable());

        ::PCCERT_CONTEXT certificate = 0;

        // Create a certificate name blob.
        ::CERT_NAME_BLOB name = { 0 };
        char cb[1000] = {0};
        name.pbData = (BYTE*)cb; 
        name.cbData = 1000;
        const ::DWORD encoding = CRYPT_ASN_ENCODING;
        if (!::CertStrToNameW(encoding, subject.data(), 0, 0,
                              name.pbData, &name.cbData, 0))
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertStrToName, error);
        }

        // Describe the key provider.
        string provider_name = provider.name();
        string container = provider.container();
        ::CRYPT_KEY_PROV_INFO info = {0};
        info.pwszContainerName = container.data();
        info.pwszProvName = provider_name.data();
        info.dwProvType = provider.type();
        info.dwFlags = CERT_SET_KEY_CONTEXT_PROP_ID;
        info.dwKeySpec = key_type;

        // Expire certificate 1 year from now.
        w32::Time expiry =
            w32::Time::now() + 1*w32::Delta::year();

        // Create the self-signed certificate.
        ::CERT_EXTENSIONS extensions;
        ::ZeroMemory(&extensions, sizeof(extensions));
        certificate = ::CertCreateSelfSignCertificate
            (provider.handle(), &name, 0, &info,
             0, 0, &expiry.data(), &extensions);
        if (certificate == 0)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertCreateSelfSignCertificate, error);
        }
        const Handle handle = claim(certificate);

        // Verify that the certificate was store on the local machine.
        const ::BOOL found = ::CryptFindCertificateKeyProvInfo
            (certificate, CRYPT_FIND_MACHINE_KEYSET_FLAG, 0);
        if (found == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            if (error == NTE_NO_KEY)
            {
                // ..?
            }
            UNCHECKED_WIN32C_ERROR(CryptFindCertificateKeyProvInfo, error);
        }

        return (Certificate(handle));
    }

    Certificate::Certificate ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Certificate::Certificate ( const Blob& blob, const Encoding& encoding )
        : myHandle(claim(::acquire(blob.data(), blob.size(), encoding)))
    {
    }

    bool Certificate::valid () const
    {
        return (::CertVerifyTimeValidity(0, myHandle->pCertInfo) == 0);
    }

    const Certificate::Handle& Certificate::handle () const
    {
        return (myHandle);
    }

    const Certificate::Encoding Certificate::Encoding::pkcs7 ()
    {
        return (PKCS_7_ASN_ENCODING);
    }

    const Certificate::Encoding Certificate::Encoding::x509 ()
    {
        return (X509_ASN_ENCODING);
    }

    Certificate::Encoding::Encoding ( Value value )
        : myValue(value)
    {
    }

    Certificate::Encoding::operator Certificate::Encoding::Value () const
    {
        return (myValue);
    }

} }
