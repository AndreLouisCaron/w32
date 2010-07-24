// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Quit.hpp>
#include <w32/gdi/post.hpp>

namespace w32 { namespace gdi {

    Quit::Quit ( uint result )
        : Message(WM_QUIT,0,0)
    {
        status(result);
    }

    Quit::Quit ( wparam wp, lparam lp )
        : Message(WM_QUIT, wp, lp)
    {
    }

    uint Quit::status () const
    {
        return (wp());
    }

    void Quit::status ( uint value )
    {
        wp(value);
    }

    void quit ( uint status )
    {
        post(Quit(status));
    }

} }
