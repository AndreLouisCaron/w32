#ifndef _win32gdi_NonmaskedImageList_HPP__
#define _win32gdi_NonmaskedImageList_HPP__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <concepts/NotCopyable.hpp>
#include "wingdi.hpp"
#include "ImageList.hpp"

namespace win32gdi {

    class NonmaskedImageList : public ImageList
    {
        /* nested types. */
    public:
        class ImageInfo
        {
            /* data. */
        private:
            BitmapProxy myImage;

            /* construction. */
        public:
            ImageInfo ( const ::IMAGEINFO& data )
                : myImage(data.hbmImage)
            {}

            ImageInfo ( const ImageInfo& other )
                : myImage(other.myImage)
            {}

            /* methods. */
        public:
            const Bitmap& image () const {
                return (myImage);
            }
        };

        /* methods. */
    public:
            /*!
             * @brief Appends an image to the list.
             * @return The image's index.
             */
        int add ( const Bitmap& image );

            /*!
             * @brief Changes an image.
             */
        void replace ( const Bitmap& image, int index );

            /*!
             * @brief Obtains info about an image.
             *
             * The returned structure gives direct access to the image
             * for any modification. Unfortunately, there is no way to
             * determine if the images are actually bitmaps, icons or
             * cursors.
             */
        ImageInfo info ( int index ) const;
    };

}

#endif /* _win32gdi_NonmaskedImageList_HPP__ */
