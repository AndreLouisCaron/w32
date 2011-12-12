// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/Static.hpp>
#include <w32.gdi/Bitmap.hpp>
#include <w32.gdi/Icon.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, L"Static", 0, standard,
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

    Static::Static ( const Handle& handle )
        : Control(handle)
    {
    }

    Static::Static ( const Rectangle& bounds )
        : Control(claim(::create(0, 0, 0, bounds.data())))
    {
    }

    Static::Static ( Window& window, const Rectangle& bounds )
        : Control(claim(
            ::create(0, WS_CHILD, window.handle(), bounds.data())
            ))
    {
    }

    void Static::text ( const string& text )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= SS_BITMAP;
        style &= SS_ICON;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::BOOL result =::SetWindowTextW(handle(), text.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetWindowText, error);
        }
    }

    string Static::text () const
    {
            // Find out exactly how much text this contains...
        const int length = ::GetWindowTextLengthW(handle());
        
            // Allocate memory.
        string text(length);
        
            // *Finally* fetch the associated text.
        const ::BOOL result =::GetWindowTextW
            (handle(), text.data(), text.size());
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetWindowText, error);
        }
        return (text);
    }

    void Static::bitmap ( const Bitmap& bitmap )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= SS_ICON;
        style |= SS_BITMAP;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::HBITMAP image = bitmap.handle();
        ::SendMessage(
            handle(), STM_SETIMAGE, ::WPARAM(IMAGE_BITMAP), ::LPARAM(image)
            );
    }

    Bitmap Static::bitmap () const
    {
            // Query the bitmap handle.
        const ::LRESULT result = ::SendMessage(
            handle(), STM_GETIMAGE, ::WPARAM(IMAGE_BITMAP), 0
            );
        return (Bitmap(Bitmap::proxy(reinterpret_cast< ::HBITMAP >(result))));
    }

    void Static::icon ( const Icon& icon )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= SS_BITMAP;
        style |= SS_ICON;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::HICON image = icon.handle();
        ::SendMessage(
            handle(), STM_SETIMAGE, ::WPARAM(IMAGE_ICON), ::LPARAM(image)
            );
    }

    Icon Static::icon () const
    {
        const ::LRESULT result = ::SendMessage(
            handle(), STM_GETIMAGE, ::WPARAM(IMAGE_ICON), 0
            );
        return (Icon(Icon::proxy(reinterpret_cast< ::HICON >(result))));
    }

} }
