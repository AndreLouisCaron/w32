// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/ListBox.hpp>
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
