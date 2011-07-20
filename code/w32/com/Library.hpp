#ifndef _w32_com_Library_hpp__
#define _w32_com_Library_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/com/Threading.hpp>

namespace w32{ namespace com {

    class Library :
        private NotCopyable
    {
        /* construction. */
    public:
        Library ( const Threading& model = Threading::multiple() );
        ~Library ();
    };

} }

#endif /* _w32_com_Library_hpp__ */
