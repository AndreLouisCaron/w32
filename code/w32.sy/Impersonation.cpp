// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.sy/Impersonation.hpp>
#include <w32.sy/Token.hpp>
#include <w32/Error.hpp>
#include <w32/string.hpp>

namespace w32 { namespace sy {

    void clear ( string& password )
    {
        ::SecureZeroMemory(password.data(), password.size()*sizeof(wchar_t));
    }

    void impersonate ( const Token& token )
    {
        const ::BOOL result = ::ImpersonateLoggedOnUser(token.handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ImpersonateLoggedOnUser, error);
        }
    }

    void revert ()
    {
        const ::BOOL result = ::RevertToSelf();
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(RevertToSelf, error);
        }
    }

    Token logon ( const string& domain,
        const string& username, const string& password )
    {
        ::HANDLE token = 0;
        const ::BOOL result = ::LogonUserW(
            username.data(), domain.data(), password.data(),
            LOGON32_LOGON_BATCH, LOGON32_PROVIDER_DEFAULT, &token
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LogonUser, error);
        }
        return (Token(Token::claim(token)));
    }

    Impersonation::Impersonation ( const Token& token )
    {
        impersonate(token);
    }

    Impersonation::~Impersonation ()
    try
    {
        revert();
    }
        // Don't leak exceptions from destructor.
    catch ( ... ) {}

} }
