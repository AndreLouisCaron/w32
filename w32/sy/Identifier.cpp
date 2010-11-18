/*!
 * @file w32/sct/Identifier.cpp
 * @author Andre Caron
 */

#include <w32/sct/Identifier.hpp>
#include <w32/dbg/UncheckedError.hpp>

namespace {

    ::PSID copy ( ::DWORD length, ::PSID model )
    {
        ::PSID duplicate = 0;
        if ( ::CopySid(length,&duplicate,model) == 0 ) {
            UNCHECKED_WIN32C_ERROR(FreeSid,::GetLastError());
        }
        return (duplicate);
    }

}

namespace w32 {
    namespace sct {

        Identifier::Identifier ( const Identifier& other )
            : myHandle(copy(other.length(),other.handle()))
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

        dword Identifier::length () const
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
                                      token.handle().value(), handle(), &member
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

    }
}
