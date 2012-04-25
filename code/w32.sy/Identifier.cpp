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
 * @file w32.sy/Identifier.cpp
 * @brief Unique identifier for a user account on the network.
 */

#include <w32.sy/Identifier.hpp>
#include <w32/Error.hpp>
#include <w32/string.hpp>
#include <w32.sy/Token.hpp>

namespace {

    ::PSID copy ( ::PSID data, ::DWORD size )
    {
        ::PSID copy = operator new(size);
        const ::BOOL status = ::CopySid(size, copy, data);
        if ( status == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CopySid, error);
        }
        return (copy);
    }

    ::PSID copy ( ::PSID data )
    {
        return (copy(data, ::GetLengthSid(data)));
    }

    ::PSID parse ( const ::WCHAR * value )
    {
        ::PSID handle = 0;
        const ::BOOL result = ::ConvertStringSidToSidW(value, &handle);
        if ( result != FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ConvertStringSidToSid, error);
        }
        return (handle);
    }

    void abandon ( ::PSID object )
    {
    }

    void destroy ( ::PSID object )
    {
        ::FreeSid(object);
    }

    void release ( ::PSID object )
    {
        operator delete(object);
    }

}

namespace w32 { namespace sy {

    Identifier::Handle Identifier::claim ( ::PSID object )
    {
        return (Handle(object, &::destroy));
    }

    Identifier::Handle Identifier::proxy ( ::PSID object )
    {
        return (Handle(object, &::abandon));
    }

    Identifier::Identifier ( const string& value )
        : myHandle(::parse(value.data()), &::destroy)
    {
    }

    Identifier::Identifier ( ::PSID data )
        : myHandle(::copy(data), &::release)
    {
    }

    Identifier::Identifier ( ::PSID data, ::DWORD size )
        : myHandle(::copy(data, size), &::release)
    {
    }

    Identifier::Identifier ( const Identifier& other )
        : myHandle(::copy(other.handle(), other.size()), &::release)
    {
    }

    Identifier::Handle Identifier::handle () const
    {
        return (myHandle);
    }

    bool Identifier::valid () const
    {
        return ( (handle() != 0) && (::IsValidSid(handle())) );
    }

    dword Identifier::size () const
    {
        if ( !valid() ) {
            return (0);
        }
        return (::GetLengthSid(handle()));
    }

    bool Identifier::in ( const Token& token ) const
    {
        ::BOOL member = FALSE;
        const ::BOOL result = ::CheckTokenMembership(
            token.handle(), handle(), &member
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(CheckTokenMembership,::GetLastError());
        }
        return (member != FALSE);
    }

    bool Identifier::operator== ( const Identifier& other ) const
    {
        return ((valid() && other.valid()) &&
            (::EqualSid(handle(),other.handle()) != 0));
    }

    bool Identifier::operator!= ( const Identifier& other ) const
    {
        return ( !((*this) == other) );
    }

    Identifier::operator string () const
    {
        ::WCHAR * value = 0;
        const ::BOOL result = ::ConvertSidToStringSidW(handle(), &value);
        if ( result != FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ConvertSidToStringSid, error);
        }
        const string sid(value);
        ::LocalFree(value);
        return (sid);
    }

    Identifier lookup ( const string& system, const string& account )
    {
        ::SID identifier; ::ZeroMemory(&identifier, sizeof(identifier));
        ::DWORD size = 0; ::SID_NAME_USE type = SidTypeUnknown;
        const ::BOOL result = ::LookupAccountNameW(
            system.data(), account.data(), &identifier, &size, 0, 0, &type
            );
        if ( result != FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LookupAccountName, error);
        }
        return (Identifier(&identifier, size));
    }

} }
