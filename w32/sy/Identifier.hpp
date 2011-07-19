#ifndef _w32_sy_Identifier_hpp__
#define _w32_sy_Identifier_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace sy {

    class Token;

    class Identifier
    {
        /* nested types. */
    public:
        typedef ::PSID Handle;

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Identifier ( const string& value );
        Identifier ( ::PSID data, ::DWORD size );
        Identifier ( const Identifier& other );
        ~Identifier();

        /* methods. */
    public:
        Handle handle () const;
        bool valid () const;
        dword size () const;

        bool in ( const Token& token ) const;

        /* operators. */
    public:
        bool operator== ( const Identifier& other ) const;
        bool operator!= ( const Identifier& other ) const;

        operator string () const;
    };

    Identifier lookup ( const string& system, const string& account );

} }

#endif /* _w32_sy_Identifier_hpp__ */
