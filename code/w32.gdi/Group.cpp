// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/Group.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, L"button", 0, standard,
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

    Group::Group ( const Handle& handle )
        : Control(handle)
    {
    }

    Group::Group ( Window& window, const Rectangle& bounds )
        : Control(claim(
              ::create(0, WS_CHILD|BS_GROUPBOX, window.handle(), bounds.data())
              ))
    {
    }

    void Group::title ( const string& title )
    {
        const ::BOOL result =::SetWindowTextW(handle(), title.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetWindowText, error);
        }
    }

    string Group::title () const
    {
            // Find out exactly how much text this contains...
        const int length = ::GetWindowTextLengthW(handle());
        
            // Allocate memory.
        string title(length);
        
            // *Finally* fetch the associated text.
        const ::BOOL result =::GetWindowTextW
            (handle(), title.data(), title.size());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetWindowText, error);
        }
        return (title);
    }

} }
