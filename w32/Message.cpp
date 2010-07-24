// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Message.hpp>

namespace w32 { namespace gdi {

    Message::Message ()
        : myMessage(0), myWParam(0), myLParam(0)
    {
    }

    Message::Message ( uint wm, wparam wp, lparam lp )
        : myMessage(wm), myWParam(wp), myLParam(lp)
    {
    }

    uint Message::wm () const
    {
        return (myMessage);
    }

    wparam Message::wp () const
    {
        return (myWParam);
    }

    lparam Message::lp () const
    {
        return (myLParam);
    }

    void Message::wp ( wparam value )
    {
        myWParam = value;
    }

    void Message::lp ( lparam value )
    {
        myLParam = value;
    }

} }
