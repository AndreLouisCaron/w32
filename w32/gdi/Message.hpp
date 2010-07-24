#ifndef _w32_gdi_Message_hpp__
#define _w32_gdi_Message_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace gdi {

    class W32_GDI_EXPORT Message
    {
        /* data. */
    private:
        uint myMessage;
        wparam myWParam;
        lparam myLParam;

        /* construction. */
    public:
        Message ();
        Message ( uint wm, wparam wp, lparam lp );

        /* methods. */
    public:
        uint wm () const;
        wparam wp () const;
        lparam lp () const;

    protected:
        void wp ( wparam value );
        void lp ( lparam value );
    };

} }

#endif /* _w32_gdi_Message_hpp__ */
