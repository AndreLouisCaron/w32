// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/UpDown.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Window.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, UPDOWN_CLASSW, 0, standard,
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

    UpDown::UpDown ( const Handle& handle )
        : Control(handle)
    {
    }

    UpDown::UpDown ( Window& window, const Rectangle& bounds )
        : Control(claim(
              ::create(0, WS_CHILD, window.handle(), bounds.data())
              ))
    {
    }

    int UpDown::base ( int radix )
    {
        const int result = static_cast<int>(::SendMessage(
            handle(), UDM_SETBASE, static_cast<::WPARAM>(radix), 0
            ));
        return (result);
    }

    int UpDown::base () const
    {
        const int result = static_cast<int>(::SendMessage(
            handle(), UDM_GETBASE, 0, 0
            ));
        return (result);
    }

    int UpDown::position ( int value )
    {
        const int result = static_cast<int>(::SendMessage(
            handle(), UDM_SETPOS32, 0, static_cast<::LPARAM>(value)
            ));
        return (result);
    }

    int UpDown::position () const
    {
        ::BOOL success = 0;
        const int result = static_cast<int>(::SendMessage(
            handle(), UDM_GETPOS32, 0,
            reinterpret_cast<::LPARAM>(&success)
            ));
        if ( success == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SendMessage,::GetLastError());
        }
        return (result);
    }

    void UpDown::range ( const Range& range )
    {
        ::SendMessage(
            handle(), UDM_SETRANGE32,
            static_cast<::WPARAM>(range.low()),
            static_cast<::LPARAM>(range.high())
            );
    }

    UpDown::Range UpDown::range () const
    {
        int low = 0;
        int high = 0;
        ::SendMessage(
            handle(), UDM_GETRANGE32,
            reinterpret_cast<::WPARAM>(&low),
            reinterpret_cast<::LPARAM>(&high)
            );
        return (Range(low,high));
    }

} }
