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

#include <w32.gdi/ListBox.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, L"listbox", 0, standard,
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

    ListBox::ListBox ( const Handle& handle )
        : Window(handle)
    {
    }

    ListBox::ListBox ( Window& window, const Rectangle& bounds )
        : Window(claim(::create(0, WS_CHILD, window.handle(), bounds.data())))
    {
    }

    int ListBox::add ( const string& entry )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_ADDSTRING, 0,
            reinterpret_cast< ::LPARAM >(entry.data())
            );
        if ( result == LB_ERR || result == LB_ERRSPACE ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
        return (int(result));
    }

    int ListBox::insert ( const string& entry, int position )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_INSERTSTRING,
            static_cast< ::WPARAM >(position),
            reinterpret_cast< ::LPARAM >(entry.data())
            );
        if ( result == LB_ERR || result == LB_ERRSPACE ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
        return (int(result));
    }

    int ListBox::append ( const string& entry )
    {
        return (insert(entry,-1));
    }

    int ListBox::remove ( int position )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_DELETESTRING,
            static_cast< ::WPARAM >(position), 0
            );
        if ( result == LB_ERR ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
        return (int(result));
    }

    int ListBox::selection () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_GETCURSEL, 0, 0
            );
        if ( result == LB_ERR ) {
            return (-1);
        }
        return (int(result));
    }

    int ListBox::selectionCount () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_GETSELCOUNT, 0, 0
            );
        if ( result == LB_ERR ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
        return (int(result));
    }

    int ListBox::selection ( int * items, int maximum ) const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_GETSELITEMS,
            static_cast< ::WPARAM >(maximum),
            reinterpret_cast< ::LPARAM >(items)
            );
        if ( result == LB_ERR ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
        return (int(result));
    }

    void ListBox::selection ( int position )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_SETCURSEL,
            static_cast<::WPARAM>(position), 0
            );
        if ( result == LB_ERR ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
    }

    void ListBox::select ( int position )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_SETSEL,
            static_cast<::WPARAM>(TRUE),
            static_cast<::LPARAM>(position)
            );
        if ( result == LB_ERR ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
    }

    void ListBox::unselect ( int position )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_SETSEL,
            static_cast<::WPARAM>(FALSE),
            static_cast<::LPARAM>(position)
            );
        if ( result == LB_ERR ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
    }

    void ListBox::selectAll ()
    {
        select(-1);
    }

    void ListBox::clearSelection ()
    {
        unselect(-1);
    }

    int ListBox::reserve ( int count, int lengths )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), LB_INITSTORAGE,
            static_cast<::WPARAM>(count),
            static_cast<::LPARAM>(lengths)
            );
        if ( result == LB_ERRSPACE ) {
            UNCHECKED_WIN32C_ERROR(SendMessageW,::GetLastError());
        }
        return (int(result));
    }

    void ListBox::clear ()
    {
        ::SendMessageW(
            handle(), LB_RESETCONTENT, 0, 0
            );
    }

} }
