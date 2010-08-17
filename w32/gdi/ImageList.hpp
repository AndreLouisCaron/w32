#ifndef _w32_gdi_ImageList_hpp__
#define _w32_gdi_ImageList_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

// TODO: Add support for masked image lists.
// TODO: Add support for image list depth.

#include "__configure__.hpp"
#include <w32/Reference.hpp>

namespace w32 { namespace gdi {

    class Color;
    class Cursor;
    class Icon;
    class Size;

        /*!
         * @brief Groups icons and bitmaps with efficient storage.
         */
    class W32_GDI_EXPORT ImageList
    {
        /* nested types. */
    public:
        typedef Reference< ::HIMAGELIST, void(*)(::HIMAGELIST) > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::HIMAGELIST object );
        static Handle proxy ( ::HIMAGELIST object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated image list.
             *
             * @see claim ()
             * @see proxy ()
             */
        explicit ImageList ( const Handle& handle );

            /*!
             * @brief Creates a new image list.
             *
             * @param size Size, in pixels, of images stored in the list.
             * @param length Number of initial items in the list.
             */
        explicit ImageList ( const Size& size, int length );

        /* methods. */
    public:
            /*!
             * @brief Obtains the image list's handle.
             */
        const Handle& handle () const;

            /*!
             * @brief Returns the number of images in the list.
             */
        int count () const;

            /*!
             * @brief Appends an image to the list.
             * @return The image's index.
             */
        int add ( const Icon& image );

            /*!
             * @brief Appends an image to the list.
             * @return The image's index.
             */
        int add ( const Cursor& image );

            /*!
             * @brief Removes an image from the list.
             *
             * This shifts all following images' indexes.
             *
             * @param index Index of the image to remove.
             */
        void remove ( int index );

            /*!
             * @brief Removes all images from the list.
             */
        void clear ();

            /*!
             * @brief Changes an image.
             */
        void replace ( const Icon& image, int index );

            /*!
             * @brief Changes an image.
             */
        void replace ( const Cursor& image, int index );

            /*!
             * @brief Changes the background colors.
             * @return The previous background color.
             */
        Color background ( const Color& color );

            /*!
             * @brief Changes the background colors.
             * @return The previous background color.
             */
        Color background () const;
    };

} }

#endif /* _w32_gdi_ImageList_hpp__ */
