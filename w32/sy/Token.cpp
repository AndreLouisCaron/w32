/*!
 * @file w32/sct/Token.cpp
 * @author Andre Caron
 */

#include <w32/sct/Token.hpp>
#include <w32/dbg/UncheckedError.hpp>

namespace w32 {
    namespace sct {

        const Token::Type Token::Type::primary(TokenPrimary);
        const Token::Type Token::Type::impersonation(TokenImpersonation);

        Token::Type::Type ( Value value )
            : myValue(value)
        {
        }

        Token::Type Token::Type::of ( const Token& token )
        {
            ::TOKEN_TYPE information = TokenImpersonation;
            ::DWORD length = 0;
            const ::BOOL result = ::GetTokenInformation(
                                      token.handle().value(), TokenType, &information,
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

        const Token::Access Token::Access::adjustdefault(TOKEN_ADJUST_DEFAULT);
        const Token::Access Token::Access::adjustgroups(TOKEN_ADJUST_GROUPS);
        const Token::Access
        Token::Access::adjustprivileges(TOKEN_ADJUST_PRIVILEGES);
        const Token::Access Token::Access::adjustsession(TOKEN_ADJUST_SESSIONID);
        const Token::Access Token::Access::assignprimary(TOKEN_ASSIGN_PRIMARY);
        const Token::Access Token::Access::duplicate(TOKEN_DUPLICATE);
        const Token::Access Token::Access::execute(TOKEN_EXECUTE);
        const Token::Access Token::Access::impersonate(TOKEN_IMPERSONATE);
        const Token::Access Token::Access::query(TOKEN_QUERY);
        const Token::Access Token::Access::querysource(TOKEN_QUERY_SOURCE);
        const Token::Access Token::Access::read(TOKEN_READ);
        const Token::Access Token::Access::write(TOKEN_WRITE);
        const Token::Access Token::Access::all(TOKEN_ALL_ACCESS);
        const Token::Access Token::Access::none(0);

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
            return (::IsTokenRestricted(handle().value()) != 0);
        }

    }
}
