// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/ListView.hpp>
#include <w32/gdi/ImageList.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, WC_LISTVIEWW, 0, standard,
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

    ListView::ListView ( const Handle& handle )
        : Control(handle)
    {
    }

    ListView::ListView ( Window& window, const Rectangle& bounds )
        : Control(claim(
              ::create(0, WS_CHILD, window.handle(), bounds.data())
              ))
    {
    }

    int ListView::insert ( const Column& column, int index )
    {
        const int result = ListView_InsertColumn(
            handle(), index, &column.data()
            );
        if ( result == -1 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ListView_InsertColumn,error);
        }
        return (result);
    }

    ListView::Column ListView::column ( int index )
    {
        ::LVCOLUMNW data;
        const ::BOOL result = ListView_GetColumn(
            handle(), index, &data
            );
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ListView_GetColumn,error);
        }
        return (Column(data));
    }

    void ListView::column ( const Column& column, int index )
    {
        const ::BOOL result = ListView_SetColumn(
            handle(), index, &column.data()
            );
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ListView_SetColumn,error);
        }
    }

    void ListView::largeIcons ( const ImageList& images )
    {
        const ::HIMAGELIST result = ListView_SetImageList(
            handle(), images.handle(),
            LVSIL_NORMAL
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ListView_SetImageList,error);
        }
    }

    void ListView::smallIcons ( const ImageList& images )
    {
        const ::HIMAGELIST result = ListView_SetImageList(
            handle(), images.handle(),
            LVSIL_SMALL
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SendMessage,error);
        }
    }

    void ListView::states ( const ImageList& images )
    {
        const ::HIMAGELIST result = ListView_SetImageList(
            handle(), images.handle(),
            LVSIL_STATE
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SendMessage,error);
        }
    }

    void ListView::backgroundColor ( const Color& color )
    {
        ListView_SetBkColor(handle(), color.value());
    }

    Color ListView::backgroundColor () const
    {
        return (Color(ListView_GetBkColor(handle())));
    }

    ListView::size_type ListView::count () const
    {
        return (ListView_GetItemCount(handle()));
    }

    void ListView::textColor ( const Color& color )
    {
        ListView_SetTextColor(handle(), color.value());
    }

    Color ListView::textColor () const
    {
        return (Color(ListView_GetTextColor(handle())));
    }

    ListView::Column::Column ()
    {
        ::ZeroMemory(&myData,sizeof(myData));
    }

    ListView::Column::Column ( const Data& data )
        : myData(data)
    {
    }

    ListView::Column::Data& ListView::Column::data ()
    {
        return (myData);
    }

    const ListView::Column::Data& ListView::Column::data () const
    {
        return (myData);
    }

    void ListView::Column::width ( int value )
    {
        myData.mask |= LVCF_WIDTH;
        myData.cx = value;
    }

    void ListView::Column::caption ( const string& caption )
    {
        myCaption = caption;
        myData.mask |= LVCF_TEXT;
        myData.mask |= LVCF_FMT;
        myData.pszText = myCaption.data();
        myData.cchTextMax = myCaption.size();
        myData.fmt = LVCFMT_LEFT;
    }

} }
