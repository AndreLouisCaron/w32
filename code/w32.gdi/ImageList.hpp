#ifndef _w32_gdi_ImageList_hpp__
#define _w32_gdi_ImageList_hpp__

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
    class ImageList
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
