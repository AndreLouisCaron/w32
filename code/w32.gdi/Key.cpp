// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/Key.hpp>

namespace w32 { namespace gdi {

    const Key Key::shift ()
    {
        return (VK_SHIFT);
    }

    const Key Key::lshift ()
    {
        return (VK_LSHIFT);
    }

    const Key Key::rshift ()
    {
        return (VK_RSHIFT);
    }

    const Key Key::control ()
    {
        return (VK_CONTROL);
    }

    const Key Key::lcontrol ()
    {
        return (VK_LCONTROL);
    }

    const Key Key::rcontrol ()
    {
        return (VK_RCONTROL);
    }

    const Key Key::menu ()
    {
        return (VK_MENU);
    }

    const Key Key::lmenu ()
    {
        return (VK_LMENU);
    }

    const Key Key::rmenu ()
    {
        return (VK_RMENU);
    }

    Key::Key ( int identifier )
        : myIdentifier(identifier)
    {
    }

    bool Key::up ( const Key& key )
    {
        return ((::GetKeyState(key.identifier()) & 0x8000) != 0);
    }

    bool Key::down ( const Key& key )
    {
        return ((::GetKeyState(key.identifier()) & 0x8000) == 0);
    }

    bool Key::toggled ( const Key& key )
    {
        return ((::GetKeyState(key.identifier()) & 0x0001) == 1);
    }

    int Key::identifier () const
    {
        return (myIdentifier);
    }

} }
