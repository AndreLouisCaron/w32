// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/TabControl.hpp>
#include <w32/gdi/ImageList.hpp>
#include <w32/gdi/Rectangle.hpp>
#include <w32/gdi/Tooltip.hpp>
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
