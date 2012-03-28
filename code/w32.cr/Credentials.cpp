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
 * @file w32.cr/Credentials.cpp
 * @brief Credentials object, identifies a peer during negotiation.
 */

#include <w32.cr/Credentials.hpp>
#include <w32.cr/Certificate.hpp>
#include <w32.cr/Store.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace cr {

    Credentials::Credentials
        ( const Store& store, const Certificate& certificate )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwVersion = SCHANNEL_CRED_VERSION;
        myData.dwFlags =
            SCH_CRED_NO_DEFAULT_CREDS |
            SCH_CRED_NO_SYSTEM_MAPPER |
            SCH_CRED_REVOCATION_CHECK_CHAIN;
        myData.hRootStore = store.handle();
        myData.dwMinimumCipherStrength = 128;
        myData.cCreds = 1;
        //myData.paCred = certificate.handle();
        
        const ::SECURITY_STATUS result = ::AcquireCredentialsHandleW(
            0, SCHANNEL_NAME_W, SECPKG_CRED_INBOUND,
            0, &myData, 0, 0, &myHandle, 0
            );
        if ( result != SEC_E_OK )
        {
            // Incompatible with GetLastError()?
        }
    }

    Credentials::~Credentials ()
    {
        ::FreeCredentialHandle(&myHandle);
    }

    ::PCredHandle Credentials::handle () const
    {
        return (const_cast<::PCredHandle>(&myHandle));
    }

} }
