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
 * @file w32.sy/authenticate.cpp
 * @brief Windows account credential validation.
 */

#include <w32.sy/authenticate.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <exception>

namespace {

    class Token
    {
        /* data. */
    private:
        ::SecBufferDesc myDescriptor;
        ::SecBuffer myBuffers[1];

        /* construction. */
    public:
        Token ( ::PVOID data=0, ::DWORD size=0 )
        {
            // Fill buffer description.
            myDescriptor.ulVersion = SECBUFFER_VERSION;
            myDescriptor.cBuffers  = 1;
            myDescriptor.pBuffers  = myBuffers;
            
            // Describe buffer data.
            myBuffers[0].BufferType = SECBUFFER_TOKEN;
            myBuffers[0].cbBuffer   = size;
            myBuffers[0].pvBuffer   = data;
        }

        /* methods. */
    public:
        ::PSecBufferDesc operator* ()
        {
            return (&myDescriptor);
        }

        void reset ( ::PVOID data=0, ::DWORD size=0 )
        {
            myBuffers[0].cbBuffer = size;
            myBuffers[0].pvBuffer = data;
        }
    };

    void serversetup ( ::PCredHandle credentials )
    {
        const ::SECURITY_STATUS status = ::AcquireCredentialsHandleW(
            0, L"NTLM", SECPKG_CRED_INBOUND, 0, 0, 0, 0, credentials, 0);
        if (FAILED(status))
        {
            throw (std::exception(" >> failed!"));
        }
    }

    void clientsetup ( ::PCredHandle credentials,
        ::PSEC_WINNT_AUTH_IDENTITY_W identity )
    {
        const ::SECURITY_STATUS status = ::AcquireCredentialsHandleW(
            0, L"NTLM", SECPKG_CRED_OUTBOUND, 0, identity, 0, 0, credentials, 0
            );
        if (FAILED(status))
        {
            throw (std::exception(" >> failed!"));
        }
    }

    ::DWORD tokensize ()
    {
        ::PSecPkgInfoW package;
        const ::SECURITY_STATUS status =
            ::QuerySecurityPackageInfoW(L"NTLM", &package);
        if (FAILED(status))
        {
            throw (std::exception(" >> failed!"));
        }
        const ::DWORD size = package->cbMaxToken;
        ::FreeContextBuffer(package);
        return (size);
    }

    void client ( ::PCredHandle credentials, ::PCtxtHandle lhs,
        ::PCtxtHandle rhs, ::PSecBufferDesc put, ::PSecBufferDesc get )
    {
        const ::DWORD format = SECURITY_NATIVE_DREP;
        ::DWORD attributes = 0;
        const ::SECURITY_STATUS status = ::InitializeSecurityContext(
            credentials, lhs, 0, 0, 0, format, put, 0, rhs, get, &attributes, 0
            );
        if (FAILED(status))
        {
            throw (std::exception(" >> failed (1)!"));
        }
        if ((status == SEC_I_COMPLETE_NEEDED) ||
            (status == SEC_I_COMPLETE_AND_CONTINUE))
        {
            const ::SECURITY_STATUS status = ::CompleteAuthToken(rhs, get);
            if ( FAILED(status) )
            {
                throw (std::exception(" >> failed (2)!"));
            }
        }
    }

    bool server ( ::PCredHandle credentials, ::PCtxtHandle lhs,
        ::PCtxtHandle rhs, ::PSecBufferDesc put, ::PSecBufferDesc get )
    {
        const ::DWORD format = SECURITY_NATIVE_DREP;
        ::DWORD attributes = 0;
        const ::SECURITY_STATUS status = ::AcceptSecurityContext(
            credentials, lhs, put, 0, format, rhs, get, &attributes, 0);
        if (FAILED(status))
        {
            if ( status == SEC_E_LOGON_DENIED ) {
                return (false);
            }
            throw (std::exception(" >> failed (1)!"));
        }
        if ((status == SEC_I_COMPLETE_NEEDED) ||
            (status == SEC_I_COMPLETE_AND_CONTINUE))
        {
            const ::SECURITY_STATUS status = ::CompleteAuthToken(rhs, get);
            if (FAILED(status))
            {
                throw (std::exception(" >> failed (2)!"));
            }
        }
        return (true);
    }

}

namespace w32 { namespace sy {

    bool authenticate ( const string& domain,
                        const string& username, const string& password )
    {
        // Fill in identity descriptor.
        ::SEC_WINNT_AUTH_IDENTITY_W identity;
        ::ZeroMemory(&identity, sizeof(identity));
        identity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
        identity.Domain         = (uint16*)domain.data();
        identity.DomainLength   =          domain.size();
        identity.User           = (uint16*)username.data();
        identity.UserLength     =          username.size();
        identity.Password       = (uint16*)password.data();
        identity.PasswordLength =          password.size();
        
        // Prepare to send credentials.
        ::CredHandle ccredentials;
        ::clientsetup(&ccredentials, &identity);
        
        // Prepare to receive credentials.
        ::CredHandle scredentials;
        ::serversetup(&scredentials);
        
        // Allocate enough memory to hold messages (tokens).
        const ::DWORD maxtokensize = ::tokensize();
        const ::PVOID ctokendata = ::malloc(maxtokensize);
        const ::PVOID stokendata = ::malloc(maxtokensize);
        
        // Client: negotiate protocol.
        ::CtxtHandle ccontext;
        ::Token ctoken(ctokendata, maxtokensize);
        ::client(&ccredentials, 0, &ccontext, 0, *ctoken);
        
        // Server: challenge client.
        ::CtxtHandle scontext;
        ::Token stoken(stokendata, maxtokensize);
        ::server(&scredentials, 0, &scontext, *ctoken, *stoken);
        
        // Client: request authentication.
        ctoken.reset(ctokendata, maxtokensize);
        ::client(&ccredentials, &ccontext, 0, *stoken, *ctoken);
        
        // Server: authenticate client.
        stoken.reset(stokendata, maxtokensize);
        const bool authenticated =
            ::server(&scredentials, &scontext, 0, *ctoken, *stoken);
        
        // Release resources.
        ::free(ctokendata);
        ::free(stokendata);
        ::DeleteSecurityContext(&ccontext);
        ::DeleteSecurityContext(&scontext);
        ::FreeCredentialHandle(&ccredentials);
        ::FreeCredentialHandle(&scredentials);

        return (authenticated);
    }

} }
