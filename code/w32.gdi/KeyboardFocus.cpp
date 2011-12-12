// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/KeyboardFocus.hpp>
#include <w32/Error.hpp>
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

    KeyboardFocus::KeyboardFocus ( Window& window )
        : myPredecessor(::SetFocus(window.handle()))
    {
        if ( myPredecessor == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetFocus,::GetLastError());
        }
    }

    KeyboardFocus::~KeyboardFocus ()
    {
        ::SetFocus(myPredecessor);
    }

} }
