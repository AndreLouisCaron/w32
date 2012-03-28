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
 * @file w32.sy/Token.hpp
 * @brief Security token & permissions.
 */

#include <w32.sy/Token.hpp>
#include <w32.sy/ImpersonationLevel.hpp>
#include <w32/Error.hpp>
#include <w32.ipc/Process.hpp>

namespace {

    ::HANDLE open ( ::HANDLE process, ::DWORD access )
    {
        ::HANDLE handle = 0;
        if ( ::OpenProcessToken(process,access,&handle) == 0 ) {
            UNCHECKED_WIN32C_ERROR(OpenProcessToken,::GetLastError());
        }
        return (handle);
    }

    ::HANDLE duplicate ( ::HANDLE model, ::SECURITY_IMPERSONATION_LEVEL level )
    {
        ::HANDLE handle = 0;
        if ( ::DuplicateToken(model,level,&handle) == 0 ) {
            UNCHECKED_WIN32C_ERROR(DuplicateToken,::GetLastError());
        }
        return (handle);
    }

}

namespace w32 { namespace sy {

    Token Token::of ( const ipc::Process& process )
    {
        return (Token(claim(::open(process.handle(), TOKEN_ALL_ACCESS))));
    }

    Token::Token ( const Handle& handle )
        : w32::Object(handle)
    {
    }

    Token::Token ( const Token& token, const ImpersonationLevel& level )
        : w32::Object(::duplicate(token.handle(), level.value()))
    {
    }

    const Token::Type Token::Type::primary ()
    {
        return (TokenPrimary);
    }

    const Token::Type Token::Type::impersonation ()
    {
        return (TokenImpersonation);
    }

    Token::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Token::Type Token::Type::of ( const Token& token )
    {
        ::TOKEN_TYPE information = TokenImpersonation;
        ::DWORD length = 0;
        const ::BOOL result = ::GetTokenInformation(
            token.handle(), TokenType, &information,
            sizeof(information), &length
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetTokenInformation,::GetLastError());
        }
        return (Type(information));
    }

    Token::Type::Value Token::Type::value () const
    {
        return (myValue);
    }

    bool Token::Type::operator== ( const Type& other ) const
    {
        return (myValue == other.myValue);
    }

    bool Token::Type::operator!= ( const Type& other ) const
    {
        return (myValue != other.myValue);
    }

    const Token::Access Token::Access::adjustdefault ()
    {
        return (TOKEN_ADJUST_DEFAULT);
    }

    const Token::Access Token::Access::adjustgroups ()
    {
        return (TOKEN_ADJUST_GROUPS);
    }

    const Token::Access
        Token::Access::adjustprivileges ()
    {
        return (TOKEN_ADJUST_PRIVILEGES);
    }

    const Token::Access Token::Access::adjustsession ()
    {
        return (TOKEN_ADJUST_SESSIONID);
    }

    const Token::Access Token::Access::assignprimary ()
    {
        return (TOKEN_ASSIGN_PRIMARY);
    }

    const Token::Access Token::Access::duplicate ()
    {
        return (TOKEN_DUPLICATE);
    }

    const Token::Access Token::Access::execute ()
    {
        return (TOKEN_EXECUTE);
    }

    const Token::Access Token::Access::impersonate ()
    {
        return (TOKEN_IMPERSONATE);
    }

    const Token::Access Token::Access::query ()
    {
        return (TOKEN_QUERY);
    }

    const Token::Access Token::Access::querysource ()
    {
        return (TOKEN_QUERY_SOURCE);
    }

    const Token::Access Token::Access::read ()
    {
        return (TOKEN_READ);
    }

    const Token::Access Token::Access::write ()
    {
        return (TOKEN_WRITE);
    }

    const Token::Access Token::Access::all ()
    {
        return (TOKEN_ALL_ACCESS);
    }

    const Token::Access Token::Access::none ()
    {
        return (0);
    }

    Token::Access::Access ( Value value )
        : myValue(value)
    {
    }

    Token::Access::Value Token::Access::value () const
    {
        return (myValue);
    }

    bool Token::Access::operator== ( const Access& other ) const
    {
        return (myValue == other.myValue);
    }

    bool Token::Access::operator!= ( const Access& other ) const
    {
        return (myValue != other.myValue);
    }

    Token::Access Token::Access::operator| ( const Token::Access& other ) const
    {
        return (Access(myValue|other.myValue));
    }

    Token::Access& Token::Access::operator|= ( const Token::Access& other )
    {
        myValue |= other.myValue;
        return (*this);
    }

    Token::Access Token::Access::operator& ( const Token::Access& other ) const
    {
        return (Access(myValue&other.myValue));
    }

    Token::Access& Token::Access::operator&= ( const Token::Access& other )
    {
        myValue &= other.myValue;
        return (*this);
    }

    bool Token::restricted () const
    {
        return (::IsTokenRestricted(handle()) != 0);
    }

} }
