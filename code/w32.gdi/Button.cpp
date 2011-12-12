// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/Button.hpp>
#include <w32.gdi/Bitmap.hpp>
#include <w32.gdi/Icon.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>

namespace {

    const ::DWORD style = WS_VISIBLE|BS_PUSHBUTTON|BS_TEXT;

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
    )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, WC_BUTTONW, 0, standard,
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

    Button::Button ( const Handle& handle )
        : Control(handle)
    {
    }

    Button::Button ( Window& window, const Rectangle& bounds )
        : Control(claim(
            ::create(0, WS_CHILD|::style, window.handle(), bounds.data())
            ))
    {
    }

    void Button::text ( const string& text )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= BS_BITMAP;
        style &= BS_ICON;
        style |= BS_TEXT;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::BOOL result =::SetWindowTextW(handle(), text.data());
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SetWindowText, ::GetLastError());
        }
    }

    string Button::text () const
    {
            // Find out exactly how much text this contains...
        const int length = ::GetWindowTextLengthW(handle());
        
            // Allocate memory.
        string text(length);
        
            // *Finally* fetch the associated text.
        const ::BOOL result =::GetWindowTextW
            (handle(), text.data(), text.size());
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(GetWindowText, ::GetLastError());
        }
        return (text);
    }

    void Button::bitmap ( const Bitmap& bitmap )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= BS_ICON;
        style &= BS_TEXT;
        style |= BS_BITMAP;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::HBITMAP image = bitmap.handle();
        ::SendMessage(
            handle(), BM_SETIMAGE, ::WPARAM(IMAGE_BITMAP), ::LPARAM(image)
            );
    }

    Bitmap Button::bitmap () const
    {
            // Query the bitmap handle.
        const ::LRESULT result = ::SendMessage(
            handle(), BM_GETIMAGE, ::WPARAM(IMAGE_BITMAP), 0
            );
        return (Bitmap(Bitmap::proxy(reinterpret_cast< ::HBITMAP >(result))));
    }

    void Button::icon ( const Icon& icon )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= BS_BITMAP;
        style &= BS_TEXT;
        style |= BS_ICON;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::HICON image = icon.handle();
        ::SendMessage(
            handle(), BM_SETIMAGE, ::WPARAM(IMAGE_ICON), ::LPARAM(image)
            );
    }

    Icon Button::icon () const
    {
        const ::LRESULT result = ::SendMessage(
            handle(), BM_GETIMAGE, ::WPARAM(IMAGE_ICON), 0
            );
        return (Icon(Icon::proxy(reinterpret_cast< ::HICON >(result))));
    }

    bool Button::pushed () const
    {
        const ::LRESULT result = ::SendMessage(
            handle(), BM_GETSTATE, 0, 0
            );
        return (result == BST_PUSHED);
    }

    bool Button::poped () const
    {
        const ::LRESULT result = ::SendMessage(
            handle(), BM_GETSTATE, 0, 0
            );
        return (result == BST_UNCHECKED);
    }

    bool Button::checked () const
    {
        const ::LRESULT result = ::SendMessage(
            handle(), BM_GETCHECK, 0, 0
            );
        return (result == BST_CHECKED);
    }

    bool Button::clear () const
    {
        const ::LRESULT result = ::SendMessage(
            handle(), BM_GETCHECK, 0, 0
            );
        return (result == BST_UNCHECKED);
    }

} }
