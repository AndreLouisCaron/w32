// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/DateTimePicker.hpp>
#include <w32/gdi/Window.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
    )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, DATETIMEPICK_CLASSW, 0, standard,
            bounds.left, bounds.top, bounds.right-bounds.left,
            bounds.bottom-bounds.top, parent, 0, ::GetModuleHandle(0), 0
            );
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(CreateWindowEx,::GetLastError());
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    DateTimePicker::DateTimePicker ( const Handle& handle )
        : Control(handle)
    {
    }

    DateTimePicker::DateTimePicker ( Window& window, const Rectangle& bounds )
        : Control(claim(
            ::create(0, WS_CHILD|WS_VISIBLE, window.handle(), bounds.data())
            ))
    {
    }

} }
