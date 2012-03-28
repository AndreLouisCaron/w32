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

#include <w32.cr/Store.hpp>
#include <w32/Error.hpp>
#include <w32/string.hpp>

namespace {

    ::HCERTSTORE acquire ( const ::WCHAR * name )
    {
        const ::DWORD flags = CERT_SYSTEM_STORE_CURRENT_USER;
        const ::HCERTSTORE handle = ::CertOpenStore(
            CERT_STORE_PROV_SYSTEM_W, 0, 0, flags, name
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertOpenStore, error);
        }
        return (handle);
    }

    ::HCERTSTORE acquire ( const ::WCHAR * path, ::DWORD encoding )
    {
        const ::HCERTSTORE handle = ::CertOpenStore(
            CERT_STORE_PROV_FILENAME_W, encoding, 0, 0, path
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertOpenStore, error);
        }
        return (handle);
    }

    void abandon ( ::HCERTSTORE object ) {}
    void release ( ::HCERTSTORE object )
    {
        const ::BOOL result = ::CertCloseStore(object, 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertCloseStore, error);
        }
    }

}

namespace w32 { namespace cr {

    const Store::Handle Store::claim ( ::HCERTSTORE object )
    {
        return (Handle(object, &::release));
    }

    const Store::Handle Store::proxy ( ::HCERTSTORE object )
    {
        return (Handle(object, &::abandon));
    }

    Store::Store ( const string& name )
        : myHandle(claim(::acquire(name.data())))
    {
    }

    Store::Store ( const string& path, const Certificate::Encoding& encoding )
        : myHandle(claim(::acquire(path.data(),encoding)))
    {
    }

    const Store::Handle& Store::handle () const
    {
        return (myHandle);
    }

    Certificate Store::add ( const Certificate& certificate )
    {
        const ::DWORD disposition = CERT_STORE_ADD_REPLACE_EXISTING;
        ::PCCERT_CONTEXT clone = 0;
        const ::BOOL result = ::CertAddCertificateContextToStore
            (handle(), certificate.handle(), disposition, &clone);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertAddCertificateContextToStore, error);
        }
        return (Certificate(Certificate::claim(clone)));
    }

    void Store::del ( const Certificate& certificate )
    {
            // Increment certificate reference count to prevent removal from
            // releasing the certificate context or or our RAII will release
            // it a second time.. damn all these non-RAII aware APIs!
        ::CertDuplicateCertificateContext(certificate.handle());
        
            // Remove the certificate from the store, decreasing it's
            // reference count. The context will be released by our object's
            // destructor, as a good RAII implementation :-)
        const ::BOOL result = ::CertDeleteCertificateFromStore
            (certificate.handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertDeleteCertificateFromStore, error);
        }
    }

} }
