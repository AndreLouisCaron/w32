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

#include <w32.gdi/TabControl.hpp>
#include <w32.gdi/ImageList.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Tooltip.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    void TabControl::insert ( const Tab& tab, int index )
    {
        const int result = TabCtrl_InsertItem(
            handle(), index, &tab.data()
            );
        if ( result == -1 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_InsertItem,error);
        }
    }

    void TabControl::clear ()
    {
        const ::BOOL result = TabCtrl_DeleteAllItems(handle());
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_DeleteAllItems,error);
        }
    }

    void TabControl::remove ( int index )
    {
        const ::BOOL result = TabCtrl_DeleteItem(handle(),index);
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_DeleteItem,error);
        }
    }

    int TabControl::selection () const
    {
        const int result = TabCtrl_GetCurSel(handle());
        if ( result == -1 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_GetCurSel,error);
        }
        return (result);
    }

    int TabControl::selection ( int index )
    {
        const int result = TabCtrl_SetCurSel(handle(),index);
        if ( result == -1 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_SetCurSel,error);
        }
        return (result);
    }

    ImageList TabControl::images () const
    {
        const ::HIMAGELIST result = TabCtrl_GetImageList(handle());
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_GetImageList,error);
        }
        return (ImageList(ImageList::claim(result)));
    }

    void TabControl::images ( const ImageList& list )
    {
        const ::HIMAGELIST result = TabCtrl_SetImageList(
            handle(), list.handle()
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_SetImageList, error);
        }
    }

    TabControl::Tab TabControl::tab ( int index ) const
    {
        ::TC_ITEMW data;
        const ::BOOL result = TabCtrl_GetItem(handle(), index, &data);
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_GetItem, error);
        }
        return (Tab(data));
    }

    void TabControl::tab ( int index, const Tab& tab )
    {
        const ::BOOL result = TabCtrl_SetItem(handle(), index, &tab.data());
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_SetItem, error);
        }
    }

    int TabControl::tabs () const
    {
        const int result = TabCtrl_GetItemCount(handle());
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_GetItemCount, error);
        }
        return (result);
    }

    int TabControl::rows () const
    {
        const int result = TabCtrl_GetRowCount(handle());
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_GetRowCount, error);
        }
        return (result);
    }

    Tooltip TabControl::tip () const
    {
        const ::HWND result = TabCtrl_GetToolTips(handle());
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TabCtrl_GetTooltips,error);
        }
        return (Tooltip(Tooltip::proxy(result)));
    }

    void TabControl::tip ( const Tooltip& help )
    {
        TabCtrl_SetToolTips(handle(), (::HWND)help.handle());
    }

    void TabControl::removeImage ( int index )
    {
        TabCtrl_RemoveImage(handle(), index);
    }

    TabControl::Tab::Tab ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    TabControl::Tab::Tab ( const Data& data )
        : myData(data)
    {
    }

    TabControl::Tab::Data& TabControl::Tab::data ()
    {
        return (myData);
    }

    const TabControl::Tab::Data& TabControl::Tab::data () const
    {
        return (myData);
    }

    void TabControl::Tab::caption ( const string& text )
    {
        myData.mask |= TCIF_TEXT;
        myData.pszText = const_cast<wchar_t*>(text.data());
    }

} }
