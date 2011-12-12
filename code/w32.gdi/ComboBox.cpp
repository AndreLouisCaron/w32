// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/ComboBox.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, L"ComboBox", 0, standard,
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

    ComboBox::size_type ComboBox::none ()
    {
        return (CB_ERR);
    }

    ComboBox::ComboBox ( const Handle& handle )
        : Control(handle)
    {
    }

    ComboBox::ComboBox ( Window& window, const Rectangle& bounds )
        : Control(Window::claim(
              ::create(0, WS_CHILD, window.handle(), bounds.data())
              ))
    {
    }

    void ComboBox::text ( const string& text )
    {
        const ::BOOL result =::SetWindowTextW(handle(), text.data());
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SetWindowText, ::GetLastError());
        }
    }

    string ComboBox::text () const
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

    ComboBox::size_type ComboBox::size () const
    {
        const ::LRESULT result = ::SendMessageW
            (handle(), CB_GETCOUNT, 0L, 0);
        if ( result == CB_ERR ) {
            UNCHECKED_WIN32C_ERROR(ComboBox_GetCount, result);
        }
        return (result);
    }

    ComboBox::size_type ComboBox::append ( const string& item )
    {
        const ::LRESULT result = ::SendMessageW
            (handle(), CB_ADDSTRING, 0L, (::LPARAM)item.data());
        if ((result == CB_ERR) || (result == CB_ERRSPACE)) {
            UNCHECKED_WIN32C_ERROR(ComboBox_AddString, result);
        }
        return (result);
    }

    void ComboBox::insert ( const string& item, size_type index )
    {
        const ::LRESULT result = ::SendMessageW
            (handle(), CB_ADDSTRING, index, (::LPARAM)item.data());
        if ((result == CB_ERR) || (result == CB_ERRSPACE)) {
            UNCHECKED_WIN32C_ERROR(ComboBox_InsertString, result);
        }
    }

    void ComboBox::del ( size_type item )
    {
        const ::LRESULT result = ::SendMessageW
            (handle(), CB_DELETESTRING, item, 0);
        if ( result == CB_ERR ) {
            UNCHECKED_WIN32C_ERROR(ComboBox_DeleteString, result);
        }
    }

    void ComboBox::clear ()
    {
        ::SendMessageW(handle(), CB_RESETCONTENT, 0, 0);
    }

    ComboBox::size_type ComboBox::selection () const
    {
            // Note: CB_ERR == none().
        const ::LRESULT result = ::SendMessageW
            (handle(), CB_GETCURSEL, 0, 0);
        return (result);
    }

    void ComboBox::select ( size_type item )
    {
        const ::LRESULT result = ::SendMessageW
            (handle(), CB_SETCURSEL, item, 0);
        if ( result == CB_ERR ) {
            UNCHECKED_WIN32C_ERROR(ComboBox_SetCurSel, result);
        }
    }

    void ComboBox::unselect ()
    {
            // This is documented to return CB_ERR even when no error occurs.
        ::SendMessageW(handle(), CB_SETCURSEL, -1, 0);
    }

} }
