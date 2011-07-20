// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Header.hpp>
#include <w32/gdi/Bitmap.hpp>
#include <w32/gdi/Rectangle.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, WC_HEADERW, 0, standard,
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

    Header::Header ( const Handle& handle )
        : Control(handle)
    {
    }

    Header::Header ( Window& window, const Rectangle& bounds )
        : Control(claim(
              ::create(0, WS_CHILD, window.handle(), bounds.data())
              ))
    {
    }

    int Header::count () const
    {
        const int result = Header_GetItemCount(handle());
        if ( result == -1 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Header_InsertItem, error);
        }
        return (result);
        }

    int Header::insert ( const Item& item, int index )
    {
        const int result = static_cast<int>(SendMessageW(
            handle(), HDM_INSERTITEM, static_cast< ::WPARAM >(index),
            reinterpret_cast< ::LPARAM >(&item.data())
            ));
        if ( result == -1 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Header_InsertItem, error);
        }
        return (result);
    }

    void Header::remove ( int index )
    {
        const int result = Header_DeleteItem(handle(), index);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Header_DeleteItem, error);
        }
    }

    Header::Item::Item ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    const Header::Item::Data& Header::Item::data () const
    {
        return (myData);
    }

    void Header::Item::text ( const string& value )
    {
        myData.mask |= HDI_TEXT;
        myData.mask |= HDI_FORMAT;
        myData.pszText = const_cast<wchar_t*>(value.data());
        myData.cchTextMax = value.size();
        myData.fmt &= ~HDF_JUSTIFYMASK;
        myData.fmt |= HDF_CENTER;
        myData.fmt |= HDF_STRING;
    }

    void Header::Item::size ( int value )
    {
        myData.mask |= HDI_WIDTH;
        myData.cxy = value;
    }

    void Header::Item::bitmap ( const Bitmap& image )
    {
        myData.mask |= HDI_BITMAP;
        myData.hbm = image.handle();
    }

} }
