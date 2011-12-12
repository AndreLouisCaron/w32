// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "MaskedImageList.hpp"

namespace win32gdi {

    int MaskedImageList::add ( const Bitmap& image, const Bitmap& mask )
    {
        const int result = ImageList_Add(
                               handle().get(), image.handle().get(), mask.handle().get()
                           );
        if ( result == -1 ) {
            UNCHECKED_WIN32GDI_ERROR(ImageList_Add,0);
        }
        return (result);
    }

    void MaskedImageList::replace (
        const Bitmap& image, const Bitmap& mask, int index
    )
    {
        const ::BOOL result = ImageList_Replace(
                                  handle().get(), index, image.handle().get(), mask.handle().get()
                              );
        if ( result == FALSE ) {
            UNCHECKED_WIN32GDI_ERROR(ImageList_Replace,0);
        }
    }

    MaskedImageList::ImageInfo MaskedImageList::info ( int index ) const
    {
        ::IMAGEINFO data;
        const ::BOOL result = ImageList_GetImageInfo(
                                  handle().get(), index, &data
                              );
        if ( result == FALSE ) {
            UNCHECKED_WIN32GDI_ERROR(ImageList_GetImageInfo,0);
        }
        return (ImageInfo(data));
    }

}
