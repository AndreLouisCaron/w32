// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/ImageList.hpp>
#include <w32.gdi/Color.hpp>
#include <w32.gdi/Cursor.hpp>
#include <w32.gdi/Icon.hpp>
#include <w32.gdi/Size.hpp>
#include <w32/Error.hpp>

namespace {

    ::HIMAGELIST create ( const ::SIZE& size, int length )
    {
        const ::HIMAGELIST handle = ImageList_Create(
            size.cx, size.cy, ILC_COLOR32, length, 1
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ImageList_Create, error);
        }
        return (handle);
    }

    void destroy ( ::HIMAGELIST object )
    {
        const ::BOOL result = ImageList_Destroy(object);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ImageList_Destroy, error);
        }
    }

    void abandon ( ::HIMAGELIST object )
    {
    }

}

namespace w32 { namespace gdi {

    ImageList::Handle ImageList::claim ( ::HIMAGELIST object )
    {
        return (Handle(object, &destroy));
    }

    ImageList::Handle ImageList::proxy ( ::HIMAGELIST object )
    {
        return (Handle(object, &abandon));
    }

    ImageList::ImageList ( const Handle& handle )
        : myHandle(handle)
    {
    }

    ImageList::ImageList ( const Size& size, int length )
        : myHandle(claim(::create(size.data(), length)))
    {
    }

    const ImageList::Handle& ImageList::handle () const
    {
        return (myHandle);
    }

    int ImageList::count () const
    {
        return (ImageList_GetImageCount(handle()));
    }

    int ImageList::add ( const Icon& image )
    {
        const int result = ImageList_AddIcon(
            handle(), image.handle()
            );
        if ( result == -1 ) {
            UNCHECKED_WIN32C_ERROR(ImageList_AddIcon,0);
        }
        return (result);
    }

    int ImageList::add ( const Cursor& image )
    {
        const Icon icon(Icon::proxy(
            reinterpret_cast<::HICON>((::HCURSOR)image.handle())
            ));
        return (add(icon));
    }

    void ImageList::remove ( int index )
    {
        const ::BOOL result = ImageList_Remove(handle(),index);
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(ImageList_Remove,0);
        }
    }

    void ImageList::clear ()
    {
        remove(-1);
    }

    void ImageList::replace ( const Icon& image, int index )
    {
        const ::BOOL result = ImageList_ReplaceIcon(
            handle(), index, image.handle()
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(ImageList_ReplaceIcon,0);
        }
    }

    void ImageList::replace ( const Cursor& image, int index )
    {
        const Icon icon(Icon::proxy(
            reinterpret_cast<::HICON>((::HCURSOR)image.handle())
            ));
        replace(icon,index);
    }

    Color ImageList::background ( const Color& color )
    {
        const Color previous = ImageList_SetBkColor(
            handle(), color.value()
            );
        return (previous);
    }

    Color ImageList::background () const
    {
        return (ImageList_GetBkColor(handle()));
    }

} }
