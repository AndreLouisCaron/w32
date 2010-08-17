#ifndef _w32_security_Identifier_hpp__
#define _w32_security_Identifier_hpp__

/*!
 * @file w32/sct/Identifier.hpp
 * @author Andre Caron
 */

#include "../__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32/sct/Token.hpp>

namespace w32 { namespace sct {

        /*!
         * @brief Security identifier.
         */
    class Identifier
    {
        /* nested types. */
    public:
        typedef ::PSID Handle;

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    private:
            // Placeholder: not sure how to create these...
        Identifier ();

    public:
        Identifier ( const Identifier& other );
        ~Identifier();

        /* methods. */
    public:
        Handle handle () const;
        bool valid () const;
        dword length () const;

        bool in ( const Token& token ) const;

        /* operators. */
    public:
        bool operator== ( const Identifier& other ) const;
        bool operator!= ( const Identifier& other ) const;
    };

} }

#endif /* _w32_security_Identifier_hpp__ */
