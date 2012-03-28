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

#include <w32.cr/Chain.hpp>
#include <w32.cr/Certificate.hpp>
#include <w32/Error.hpp>

namespace {

    ::PCCERT_CHAIN_CONTEXT acquire ( ::PCCERT_CONTEXT certificate )
    {
        ::CERT_CHAIN_PARA data = { 0 };
        ::PCCERT_CHAIN_CONTEXT handle = 0;
        const ::BOOL result = ::CertGetCertificateChain
            (0, certificate, 0, 0, &data, 0, 0, &handle);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertGetCertificateChain, error);
        }
        return (handle);
    }

}

namespace w32 { namespace cr {

    Chain::Chain ( const Certificate& certificate )
    {
    }

    bool Chain::revoked ( const Certificate& certificate ) const
    {
        const ::DWORD encoding = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
        
        ::PCCERT_CONTEXT certificates[2] = { certificate.handle(), 0 };
        ::CERT_REVOCATION_STATUS status;
        const ::SECURITY_STATUS result = ::CertVerifyRevocation
            (encoding, CERT_CONTEXT_REVOCATION_TYPE,
            1, (void**)certificates, 0, 0, &status
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CertGetCertificateChain, error);
        }
        return (true);
    }

} }
