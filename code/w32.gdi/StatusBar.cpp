// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/StatusBar.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32/string.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, STATUSCLASSNAMEW, 0, standard,
            bounds.left, bounds.top, bounds.right-bounds.left,
            bounds.bottom-bounds.top, parent, 0, ::GetModuleHandle(0), 0
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateWindowEx, error);
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    StatusBar::StatusBar ( const Handle& handle )
        : Control(handle)
    {
    }


    StatusBar::StatusBar ( Window& window, const Rectangle& bounds )
        : Control(claim(
              ::create(0, WS_CHILD, window.handle(), bounds.data())
              ))
    {
    }

        // Can have multiple "parts".
    void StatusBar::caption ( const string& caption )
    {
        const ::BOOL result = static_cast< ::BOOL >(::SendMessageW(
            handle(), SB_SETTEXT, 0,
            reinterpret_cast< ::LPARAM >(caption.data())
            ));
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SendMessage, error);
        }
    }

} }
