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
 * @file w32.sy/ImpersonationLevel.cpp
 * @brief User context impersonation services.
 */

#include <w32.sy/ImpersonationLevel.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace sy {

    const ImpersonationLevel ImpersonationLevel::anonymous ()
    {
        return (SecurityAnonymous);
    }

    const ImpersonationLevel ImpersonationLevel::identification ()
    {
        return (SecurityIdentification);
    }

    const ImpersonationLevel ImpersonationLevel::impersonation ()
    {
        return (SecurityImpersonation);
    }

    const ImpersonationLevel ImpersonationLevel::delegation ()
    {
        return (SecurityDelegation);
    }

    ImpersonationLevel::ImpersonationLevel ( Value value )
        : myValue(value)
    {
    }

    ImpersonationLevel ImpersonationLevel::of ( const Token& token )
    {
        ::SECURITY_IMPERSONATION_LEVEL information = SecurityAnonymous;
        ::DWORD length = 0;
        const ::BOOL result = ::GetTokenInformation
            (token.handle(), TokenImpersonationLevel,
             &information, sizeof(information), &length);
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetTokenInformation,::GetLastError());
        }
        return (ImpersonationLevel(information));
    }

    ::SECURITY_IMPERSONATION_LEVEL ImpersonationLevel::value () const
    {
        return (myValue);
    }

    bool ImpersonationLevel::operator==
        ( const ImpersonationLevel& other ) const
    {
        return (myValue == other.myValue);
    }

    bool ImpersonationLevel::operator!=
        ( const ImpersonationLevel& other ) const
    {
        return (myValue != other.myValue);
    }

} }
