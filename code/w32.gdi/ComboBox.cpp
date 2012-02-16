// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
