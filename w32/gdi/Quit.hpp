#ifndef _win32c_gdi_Quit_hpp__
#define _win32c_gdi_Quit_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Message.hpp>

namespace w32 { namespace gdi {

    class W32_GDI_EXPORT Quit :
        public Message
    {
        /* construction. */
    public:
        explicit Quit ( uint result = 0 );
        Quit ( wparam wp, lparam lp );

        /* methods. */
    public:
        uint status () const;
        void status ( uint value );
    };

    W32_GDI_EXPORT void quit ( uint status = 0 );

} }

#endif /* _win32c_gdi_Quit_hpp__ */
