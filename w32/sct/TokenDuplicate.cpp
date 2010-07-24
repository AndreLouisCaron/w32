/*!
 * @file w32/sct/TokenDuplicate.cpp
 * @author Andre Caron
 */

#include <w32/sct/TokenDuplicate.hpp>
#include <w32/dbg/UncheckedError.hpp>

namespace {

    ::HANDLE duplicate ( ::HANDLE model, ::SECURITY_IMPERSONATION_LEVEL level )
    {
        ::HANDLE handle = 0;
        if ( ::DuplicateToken(model,level,&handle) == 0 ) {
            UNCHECKED_WIN32C_ERROR(DuplicateToken,::GetLastError());
        }
        return (handle);
    }

}

namespace w32 {
    namespace sct {

        TokenDuplicate::TokenDuplicate (
            const Token& model, const ImpersonationLevel& level
        )
            : Object::Owner(duplicate(model.handle().value(),level.value()))
        {
        }

    } }
