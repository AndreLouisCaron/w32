#ifndef _w32_sy_Impersonation_hpp__
#define _w32_sy_Impersonation_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace sy {

    class Token;

    void clear ( string& password );

    Token logon ( const string& domain,
        const string& username, const string& password );

    void impersonate ( const Token& token );
    void revert ();

    class Impersonation :
        public NotCopyable
    {
        /* construction. */
    public:
        Impersonation ( const Token& token );
        ~Impersonation ();
    };

} }

#endif /* _w32_sy_Impersonation_hpp__ */
