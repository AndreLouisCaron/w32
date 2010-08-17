#ifndef _w32_security_TokenDuplicate_hpp__
#define _w32_security_TokenDuplicate_hpp__

/*!
 * @file w32/sct/TokenDuplicate.hpp
 * @author Andre Caron
 */

#include "../__configure__.hpp"
#include <w32/sct/Token.hpp>
#include <w32/sct/ImpersonationLevel.hpp>

namespace w32 { namespace sct {

        /*!
         * @brief Creates an impersonation token.
         */
    class TokenDuplicate :
        public Token,
        public Object::Owner
    {
        /* construction. */
    public:
        explicit TokenDuplicate (
            const Token& model, const ImpersonationLevel& level
            );
    };

} }

#endif /* _w32_security_TokenDuplicate_hpp__ */
