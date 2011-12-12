// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/Edit.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
    )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, L"edit", 0, standard,
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

    Edit::Edit ( const Handle& handle )
        : Control(handle)
    {
    }

    Edit::Edit ( Window& window, const Rectangle& bounds )
        : Control(claim(
              ::create(0, WS_CHILD, window.handle(), bounds.data())
              ))
    {
    }

    void Edit::obfuscator ( wchar_t character )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style |= ES_PASSWORD;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
            // Set the password character.
        ::SendMessageW(
            handle(), EM_SETPASSWORDCHAR, ::WPARAM(character), 0
            );
    }

} }
