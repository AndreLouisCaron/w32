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

#include <w32.gdi/TreeView.hpp>
#include <w32.gdi/Color.hpp>
#include <w32.gdi/ImageList.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Window.hpp>
#include <w32/Error.hpp>

namespace {

    const ::DWORD style = WS_VISIBLE|WS_BORDER|TVS_HASBUTTONS|TVS_LINESATROOT|TVS_HASLINES;

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, WC_TREEVIEWW, 0, standard,
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

    const TreeView::Item TreeView::root ()
    {
        return (Item(TVI_ROOT));
    } 

    const TreeView::Item TreeView::first ()
    {
        return (Item(TVI_FIRST));
    }

    const TreeView::Item TreeView::last ()
    {
        return (Item(TVI_LAST));
    }

    TreeView::TreeView ( const Handle& handle )
        : Control(handle)
    {
    }

    TreeView::TreeView ( Window& window, const Rectangle& bounds )
        : Control(claim(
            ::create(0, WS_CHILD|::style, window.handle(), bounds.data())
        ))
    {
    }

    TreeView::Item TreeView::insert ( const Insertion& insertion )
    {
        const ::HTREEITEM item = reinterpret_cast< ::HTREEITEM >
            (::SendMessageW(handle(), TVM_INSERTITEMW, 0,
            reinterpret_cast< ::LPARAM >(&insertion.data())));
        if ( item == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TreeView_InsertItem, error);
        }
        return (Item(item));
    }

    void TreeView::expand ( const Item& item )
    {
        const ::BOOL result = TreeView_Expand(
            handle(), TVE_EXPAND, item.handle()
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(TreeView_Expand,::GetLastError());
        }
    }

    void TreeView::collapse ( const Item& item )
    {
        const ::BOOL result = TreeView_Expand(
            handle(), TVE_COLLAPSE, item.handle()
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(TreeView_Expand,::GetLastError());
        }
    }

    TreeView::size_type TreeView::count () const
    {
        return (TreeView_GetCount(handle()));
    }

    TreeView::Item TreeView::parent ( const Item& item ) const
    {
        const ::HTREEITEM parent(
            TreeView_GetParent(handle(),item.handle())
            );
        return (Item(parent));
    }

    void TreeView::backgroundColor ( const Color& color )
    {
        TreeView_SetBkColor(handle(),color.value());
    }

    Color TreeView::backgroundColor () const
    {
        return (Color(TreeView_GetBkColor(handle())));
    }

    void TreeView::textColor ( const Color& color )
    {
        TreeView_SetTextColor(handle(),color.value());
    }

    Color TreeView::textColor () const
    {
        return (Color(TreeView_GetTextColor(handle())));
    }

    void TreeView::lineColor ( const Color& color )
    {
        TreeView_SetLineColor(handle(),color.value());
    }

    Color TreeView::lineColor () const
    {
        return (Color(TreeView_GetLineColor(handle())));
    }

    void TreeView::images ( const ImageList& images )
    {
        TreeView_SetImageList(handle(), images.handle(), TVSIL_NORMAL);
    }

    ImageList TreeView::images () const
    {
        return (ImageList(ImageList::proxy(
            TreeView_GetImageList(handle(), TVSIL_NORMAL))));
    }

    TreeView::Item::Item ( Handle handle )
        : myHandle(handle)
    {
    }

    TreeView::Item::Handle TreeView::Item::handle () const
    {
        return (myHandle);
    }

    TreeView::Insertion::Insertion ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.hParent = TVI_ROOT;
        myData.hInsertAfter = TVI_FIRST;
    }

    TreeView::Insertion::Insertion ( Item& parent )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.hParent = parent.handle();
        myData.hInsertAfter = TVI_LAST;
    }

    TreeView::Insertion::Data& TreeView::Insertion::data ()
    {
        return (myData);
    }

    const TreeView::Insertion::Data& TreeView::Insertion::data () const
    {
        return (myData);
    }

    void TreeView::Insertion::caption ( const string& caption )
    {
        myCaption = caption;
        myData.item.pszText = myCaption.data();
        myData.item.cchTextMax = myCaption.size();
        myData.item.mask |= TVIF_TEXT;
    }

    void TreeView::Insertion::parent ( Item& parent )
    {
        myData.hParent = parent.handle();
        myData.hInsertAfter = parent.handle();
    }

    void TreeView::Insertion::children ( size_type children )
    {
        myData.item.cChildren = children;
        myData.item.mask |= TVIF_CHILDREN;
    }

    void TreeView::Insertion::image ( size_type image )
    {
        myData.item.iImage = image;
        myData.item.mask |= TVIF_IMAGE;
    }

    void TreeView::Insertion::images ( size_type normal, size_type selected )
    {
        myData.item.iImage = normal;
        myData.item.mask |= TVIF_IMAGE;

        myData.item.iSelectedImage = selected;
        myData.item.mask |= TVIF_SELECTEDIMAGE;
    }

} }
