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

#include <w32.gdi/Header.hpp>
#include <w32.gdi/Bitmap.hpp>
#include <w32.gdi/Rectangle.hpp>
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
