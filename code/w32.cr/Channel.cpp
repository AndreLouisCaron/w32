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
 * @file w32.cr/Channel.cpp
 * @brief Cryptographic encoder/decoder for SSL and TLS.
 */

#include <w32.cr/Channel.hpp>
#include <w32.cr/Certificate.hpp>
#include <w32.cr/Store.hpp>
#include <w32/string.hpp>

namespace {

    void serversetup
        ( ::PCredHandle credentials, ::PCCERT_CONTEXT certificate )
    {
        ::SEC_WCHAR package[] = SCHANNEL_NAME_W;
        
            // Wrap server credentials.
        ::PCCERT_CONTEXT certificates[] = { certificate };
        ::SCHANNEL_CRED identity;
        ::ZeroMemory(&identity, sizeof(identity));
        identity.dwVersion = SCHANNEL_CRED_VERSION;
        identity.dwFlags =
            SCH_CRED_NO_DEFAULT_CREDS |
            SCH_CRED_NO_SYSTEM_MAPPER |
            SCH_CRED_REVOCATION_CHECK_CHAIN;
        identity.dwMinimumCipherStrength = 128;
        identity.paCred = certificates;
        identity.cCreds = 1;
        
            // Acquire the handle.
        const ::DWORD use = SECPKG_CRED_INBOUND;
        const ::SECURITY_STATUS result = ::AcquireCredentialsHandleW(
            0, package, use, 0, &identity, 0, 0, credentials, 0
            );
        if ( FAILED(result) )
        {
            throw (std::exception("  >> failed!"));
        }
    }

    void clientsetup ( ::PCredHandle credentials )
    {
        ::SEC_WCHAR package[] = SCHANNEL_NAME_W;
        
            // Wrap client credentials.
        ::SCHANNEL_CRED identity;
        ::ZeroMemory(&identity, sizeof(identity));
        identity.dwVersion = SCHANNEL_CRED_VERSION;
        identity.dwFlags =
            SCH_CRED_NO_DEFAULT_CREDS |
            SCH_CRED_NO_SYSTEM_MAPPER |
            SCH_CRED_REVOCATION_CHECK_CHAIN;
        
            // Acquire the handle.
        const ::DWORD use = SECPKG_CRED_OUTBOUND;
        const ::SECURITY_STATUS status = ::AcquireCredentialsHandleW(
            0, package, use, 0, &identity, 0, 0, credentials, 0
            );
        if ( FAILED(status) )
        {
            throw (std::exception("  >> failed!"));
        }
    }

    ::DWORD tokensize ()
    {
        ::SEC_WCHAR package[] = SCHANNEL_NAME_W;
        
        ::PSecPkgInfoW info;
        const ::SECURITY_STATUS status =
            ::QuerySecurityPackageInfoW(package, &info);
        if ( FAILED(status) ) {
            throw (std::exception("  >> failed!"));
        }
        const ::DWORD size = info->cbMaxToken;
        ::FreeContextBuffer(info);
        return (size);
    }

    ::SecPkgContext_StreamSizes streamsizes ( ::PCtxtHandle context )
    {
        ::SecPkgContext_StreamSizes sizes;
        const ::SECURITY_STATUS status = ::QueryContextAttributes
            (context, SECPKG_ATTR_STREAM_SIZES, &sizes);
        if ( FAILED(status) )
        {
            // ...throw!
        }
        return (sizes);
    }

    ::SECURITY_STATUS client ( ::PCredHandle credentials, ::PCtxtHandle lhs,
        ::PCtxtHandle rhs, ::PSecBufferDesc put,
        ::PSecBufferDesc get, ::SEC_WCHAR * target )
    {
        const ::DWORD request =
            ISC_REQ_SEQUENCE_DETECT   |
            ISC_REQ_REPLAY_DETECT     |
            ISC_REQ_CONFIDENTIALITY   |
            ISC_RET_EXTENDED_ERROR    |
            ISC_REQ_ALLOCATE_MEMORY   |
            ISC_REQ_STREAM            |
            ISC_REQ_MANUAL_CRED_VALIDATION;
        
        ::DWORD attributes = 0;
        ::SECURITY_STATUS status = ::InitializeSecurityContextW(
            credentials, lhs, target, request, 0,
            0, put, 0, rhs, get, &attributes, 0
            );
        std::cout
            << "client:\n  -- 0x" << reinterpret_cast<void*>(status)
            << std::endl;
        if ( FAILED(status) && (status != SEC_E_INCOMPLETE_MESSAGE) )
        {
            throw (std::exception("  >> failed (1)!"));
        }
        if ((status == SEC_I_COMPLETE_NEEDED) ||
            (status == SEC_I_COMPLETE_AND_CONTINUE))
        {
            const ::SECURITY_STATUS status = ::CompleteAuthToken(rhs, get);
            std::cout
                << "  -- 0x" << reinterpret_cast<void*>(status)
                << std::endl;
            if ( FAILED(status) )
            {
                throw (std::exception("  >> failed (2)!"));
            }
        }
        return (status);
    }

    ::SECURITY_STATUS server ( ::PCredHandle credentials, ::PCtxtHandle lhs,
        ::PCtxtHandle rhs, ::PSecBufferDesc put, ::PSecBufferDesc get )
    {
        const ::DWORD request = ASC_REQ_ALLOCATE_MEMORY;
        
        ::DWORD attributes = 0;
        ::SECURITY_STATUS status = ::AcceptSecurityContext(
            credentials, lhs, put, request, 0, rhs, get, &attributes, 0);
        std::cout
            << "server:\n  -- 0x" << reinterpret_cast<void*>(status)
            << std::endl;
        if ( FAILED(status) && (status != SEC_E_INCOMPLETE_MESSAGE) )
        {
            throw (std::exception("  >> failed (1)!"));
        }
        if ((status == SEC_I_COMPLETE_NEEDED) ||
            (status == SEC_I_COMPLETE_AND_CONTINUE))
        {
            ::SECURITY_STATUS status = ::CompleteAuthToken(rhs, get);
            std::cout
                << "  -- 0x" << reinterpret_cast<void*>(status)
                << std::endl;
            if ( FAILED(status) )
            {
                throw (std::exception("  >> failed (2)!"));
            }
        }
        return (status);
    }

    ::SECURITY_STATUS decrypt ( ::PCtxtHandle context, ::PSecBufferDesc buffer )
    {
        const ::SECURITY_STATUS result =
            ::DecryptMessage(context, buffer, 0, 0);
        if ( FAILED(result) && (result != SEC_E_INCOMPLETE_MESSAGE) )
        {
            // ...throw!
        }
        return (result);
    }

    ::SECURITY_STATUS encrypt ( ::PCtxtHandle context, ::PSecBufferDesc buffer )
    {
        const ::SECURITY_STATUS result =
            ::EncryptMessage(context, 0, buffer, 0);
        std::cout << "  -- 0x" << reinterpret_cast<void*>(result) << std::endl;
        if ( FAILED(result) )
        {
            throw (std::exception("  >> failed!"));
        }
        return (result);
    }

    class EmptyBuffer : public w32::cr::Buffer<1>
    {
        /* construction. */
    public:
        EmptyBuffer ()
        {
            empty(0);
        }
    };

    class TokenBuffer : public w32::cr::Buffer<2>
    {
        /* construction. */
    public:
        TokenBuffer ()
        {
            token(0);
            empty(1);
        }

        /* methods. */
    public:
        void alloc ()
        {
            stuff(0, tokensize());
        }

        void clear ()
        {
            Buffer<2>::clear(0);
        }

        friend w32::net::StreamSocket& operator>>
            ( w32::net::StreamSocket& in, TokenBuffer& out )
        {
            const w32::dword capacity = out.capacity(0);
            ::SecBuffer& buffer = out[0];
            w32::byte * begin = static_cast<w32::byte*>(buffer.pvBuffer);
            w32::dword offset = buffer.cbBuffer;
            
            const int received = in.get(begin, capacity-offset);
            if ( received == 0 ) {
                throw (std::exception("  >> connection lost!"));
            }
            std::cout << "  -- received " << received << " bytes!" << std::endl;
            buffer.cbBuffer += received;
            return (in);
        }

        friend w32::net::StreamSocket& operator<<
            ( w32::net::StreamSocket& out, const TokenBuffer& in )
        {
            const ::SecBuffer& buffer = in[0];
            const w32::uint8 * begin =
                static_cast<const w32::uint8*>(buffer.pvBuffer);
            const w32::uint8 *const end = begin + buffer.cbBuffer;
            while ( begin < end )
            {
                const int sent = out.put(begin, end-begin);
                if ( sent == 0 ) {
                    throw (std::exception("  >> connection lost!"));
                }
                std::cout << "  -- sent " << sent << " bytes!" << std::endl;
                begin += sent;
            }
            return (out);
        }
    };

    class DecryptBuffer : public w32::cr::Buffer<4>
    {
        /* construction. */
    public:
        DecryptBuffer
            ( ::PVOID data=0, ::DWORD size=0, ::PCtxtHandle context=0 )
        {
            const ::SecPkgContext_StreamSizes sizes = streamsizes(context);
            
            stream(0, sizes.cbMaximumMessage);
            store (0, data, size);
            empty (1);
            empty (2);
            empty (3);
        }
    };

    class EncryptBuffer : public w32::cr::Buffer<4>
    {
        /* construction. */
    public:
        EncryptBuffer ( ::PVOID data=0, ::DWORD size=0, ::PCtxtHandle context=0 )
        {
            const ::SecPkgContext_StreamSizes sizes = streamsizes(context);
            
            header(0, sizes.cbHeader);
            stream(1, sizes.cbMaximumMessage);
            store (1, data, size);
            footer(2, sizes.cbTrailer);
            empty (3);
        }
    };

}

namespace w32 { namespace cr {

    Channel::Channel ( const w32::net::tcp::Stream& stream )
        : myStream(stream)
    {
    }

    w32::net::tcp::Stream& Channel::stream ()
    {
        return (myStream);
    }

    void Channel::client ( const string& server )
    {
        ::SECURITY_STATUS status = SEC_E_OK;
        
            // Acquire a credentials handle for authentication.
        std::cout << "client: acquiring credentials handle." << std::endl;
        ::CredHandle credentials; ::clientsetup(&credentials);
        
            // Generate client request token.
        std::cout << "client: negotiating protocal." << std::endl;
        {
                // Have the token generated.
            ::EmptyBuffer get;
            ::TokenBuffer put;
            status = ::client(
                &credentials, 0, &myContext, *get,
                *put, const_cast< ::LPWSTR >(server.data())
                );
            if ( status != SEC_I_CONTINUE_NEEDED )
            {
                // ...throw!
            }
            
                // Send client request token.
            myStream << put;
        }
        
            // Get client response token.
        std::cout << "client: requesting authentication." << std::endl;
        status = SEC_E_INCOMPLETE_MESSAGE;
        ::TokenBuffer get; get.alloc();
        ::TokenBuffer put;
        do {
                // Get some input data.
            myStream >> get;
            
                // Maybe we have enough data now.
            status = ::client(&credentials, &myContext, 0,
                *get, *put, const_cast< ::LPWSTR >(server.data()));
        }
        while ( status == SEC_E_INCOMPLETE_MESSAGE );
        
            // Send client returned token.
        myStream << put;
        put.clear();
        get.clear();
        
            // Get server returned token.
        std::cout << "client: authenticating server." << std::endl;
        status = SEC_E_INCOMPLETE_MESSAGE;
        do {
                // Get some input data.
            myStream >> get;
            
                // Maybe we have enough data now.
            status = ::client(&credentials, &myContext, 0,
                *get, *put, const_cast< ::LPWSTR >(server.data()));
        }
        while ( status == SEC_E_INCOMPLETE_MESSAGE );
        
            // Make sure we've completed.
        if ( status != SEC_E_OK )
        {
            // ...throw!
        }
        
        std::cout << "client: over and out!" << std::endl;
    }

    void Channel::server ( const Certificate& certificate )
    {
        ::SECURITY_STATUS status = SEC_E_OK;
        
            // Acquire a credentials handle for authentication.
        std::cout << "server: acquiring credentials handle." << std::endl;
        ::CredHandle credentials;
        ::serversetup(&credentials, certificate.handle());
        
            // Get client request token.
        std::cout << "server: challenging client." << std::endl;
        status = SEC_E_INCOMPLETE_MESSAGE;
        ::TokenBuffer get; get.alloc();
        ::TokenBuffer put;
        do {
                // Get some input data.
            myStream >> get;
            
                // Maybe we have enough data now.
            status = ::server
                (&credentials, 0, &myContext, *get, *put);
        }
        while ( status == SEC_E_INCOMPLETE_MESSAGE );
        
            // Make sure we can proceed.
        if ( status != SEC_I_CONTINUE_NEEDED )
        {
            // ...throw!
        }
        
            // Send client response token.
        myStream << put;
        put.clear();
        get.clear();
        
            // Get client returned token.
        std::cout << "server: authenticating client." << std::endl;
        status = SEC_E_INCOMPLETE_MESSAGE;
        do {
                // Get some input data.
            myStream >> get;
            
                // Maybe we have enough data now.
            status = ::server
                (&credentials, &myContext, 0, *get, *put);
        }
        while ( status == SEC_E_INCOMPLETE_MESSAGE );
        
            // Make sure we've completed.
        if ( status != SEC_E_OK )
        {
            // ...throw!
        }
        
            // Send client response token.
        myStream << put;
        put.clear();
        
        std::cout << "server: over and out!" << std::endl;
    }

    int Channel::get ( void * data, int size )
    {
        ::DecryptBuffer get(data, size, &myContext);
        
            // Get client request token.
        const ::SECURITY_STATUS status = ::decrypt(&myContext, *get);
        if ( status == SEC_E_INCOMPLETE_MESSAGE ) {
            return (-1);
        }
        
        if ( status == SEC_I_CONTEXT_EXPIRED )
        {
            // ...remove shutdown initiated!
        }
        
        if ( status == SEC_I_RENEGOTIATE )
        {
            // ...re-enter client/server loop!
        }
        
        if ( status != SEC_E_OK )
        {
            // ...throw!
        }
        
            // Look for data and extra buffers!
        for ( int i = 0; (i < 4); ++i )
        {
            if ( get.isstream(i) ) {
                return (get.fetch(i, data, size));
            }
        }
        return (0);
    }

    w32::net::tcp::Stream& operator<<
        ( w32::net::tcp::Stream& out, const ::SecBuffer& buffer )
    {
        const w32::uint8 * begin =
            static_cast<const w32::uint8*>(buffer.pvBuffer);
        const w32::uint8 *const end = begin + buffer.cbBuffer;
        while ( begin < end )
        {
            const int sent = out.put(begin, end-begin);
            if ( sent == 0 ) {
                throw (std::exception("  >> connection lost!"));
            }
            std::cout << "  -- sent " << sent << " bytes!" << std::endl;
            begin += sent;
        }
        return (out);
    }

    int Channel::put ( void * data, int size )
    {
        ::EncryptBuffer put(data, size, &myContext);
        
            // Encrypt the outgoing data.
        ::encrypt(&myContext, *put);
        
            // Send encrypted data.
        for ( int i = 0; (i < 3); ++i ) {
            myStream << put[i];
        }
        
        return (size);
    }

} }
