#ifndef _win32gdi_MaskedImageList_HPP__
#define _win32gdi_MaskedImageList_HPP__

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

    class MaskedImageList : public ImageList
    {
        /* nested types. */
    public:
        class ImageInfo
        {
            /* data. */
        private:
            BitmapProxy myImage;
            BitmapProxy myMask;

            /* construction. */
        public:
            ImageInfo ( const ::IMAGEINFO& data )
                : myImage(data.hbmImage),
                  myMask(data.hbmMask)
            {}

            ImageInfo ( const ImageInfo& other )
                : myImage(other.myImage),
                  myMask(other.myMask)
            {}

            /* methods. */
        public:
            const Bitmap& image () const {
                return (myImage);
            }

            const Bitmap& mask () const {
                return (myMask);
            }
        };

        /* methods. */
    public:
            /*!
             * @brief Add a masked image.
             */
        int add ( const Bitmap& image, const Bitmap& mask );

            /*!
             * @brief Changes a masked image.
             */
        void replace ( const Bitmap& image, const Bitmap& mask, int index );

            /*!
             * @brief Obtains info about an image.
             *
             * The returned structure gives direct access to the image
             * and it's mask for any modification. Unfortunately, there
             * is no way to determine if the images are actually bitmaps,
             * icons or cursors.
             */
        ImageInfo info ( int index ) const;
    };

}

#endif /* _win32gdi_MaskedImageList_HPP__ */
