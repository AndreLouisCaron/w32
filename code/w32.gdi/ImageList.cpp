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
