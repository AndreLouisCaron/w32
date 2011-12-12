// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.sy/Identifier.hpp>
#include <w32/Error.hpp>
#include <w32/string.hpp>
#include <w32.sy/Token.hpp>

namespace {

    ::PSID copy ( ::DWORD length, ::PSID model )
    {
        ::PSID duplicate = 0;
        if ( ::CopySid(length,&duplicate,model) == 0 ) {
            UNCHECKED_WIN32C_ERROR(FreeSid,::GetLastError());
        }
        return (duplicate);
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

}

namespace w32 { namespace sy {

    Identifier::Identifier ( const string& value )
        : myHandle(::parse(value.data()))
    {
    }

    Identifier::Identifier ( ::PSID data, ::DWORD size )
        : myHandle( ::copy(size, data) )
    {
    }

    Identifier::Identifier ( const Identifier& other )
        : myHandle( ::copy(other.size(),other.handle()) )
    {
    }

    Identifier::~Identifier()
    {
        if ( ::FreeSid(myHandle) != 0 ) {
            UNCHECKED_WIN32C_ERROR(FreeSid,::GetLastError());
        }
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
