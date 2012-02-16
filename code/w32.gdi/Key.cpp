// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
