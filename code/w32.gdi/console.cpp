// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/console.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    Window console ()
    {
        const ::HWND handle = ::GetConsoleWindow();
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetConsoleWindow, error);
        }
        return (Window(Window::proxy(handle)));
    }

} }
