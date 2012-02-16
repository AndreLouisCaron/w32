#ifndef _w32_gdi_DeviceContext_hpp__
#define _w32_gdi_DeviceContext_hpp__

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

#include "__configure__.hpp"
#include <w32/Reference.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

    class Brush;
    class Device;
    class DeviceCompatibleBitmap;
    class DeviceIndependantBitmap;
    class EnhancedMetafile;
    class ImageList;
    class MappingMode;
    class Metafile;
    class PixelFormat;
    class Point;
    class Rectangle;
    class Region;
    class Window;

        /*!
         * @brief Wraps access to the context used for drawing operations.
         */
    class DeviceContext
    {
        /* nested types. */
    public:
            /*!
             * @brief Function object for Handle cleanup.
             */
        class Cleanup
        {
            /* nested types. */
        public:
                // Function with extra window handle argument.
            typedef void(*Backend)(::HDC, ::HWND);

            /* data. */
        private:
            Backend myBackend;
            ::HWND mySource;

            /* construction. */
        public:
            explicit Cleanup ( Backend backend, ::HWND source = 0 );

            /* operators. */
        public:
                // Invokes cleanup.
            void operator() ( ::HDC object ) const;
        };

            /*!
             * @brief Shared pointer to a device context handle.
             */
        typedef Reference< ::HDC, Cleanup > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::HDC object );
        static Handle proxy ( ::HDC object );

            /*!
             * @brief Obtains a device context for the display (virtual screen
             *   spanning all monitors).
             *
             * @note The display is always rectangular, even if two screens have
             *   different heights.
             */
        static DeviceContext display ();

            /*!
             * @brief Creates a compatible device context.
             * @note This is not a constructor to avoid it being confused with a
             *   copy constructor, which should only create an alias.
             */
        static DeviceContext compatible ( const DeviceContext& other );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
            /*!
             * @brief Wraps a pre-allocated device context.
             *
             * @see Handle
             * @see claim()
             * @see proxy()
             */
        explicit DeviceContext ( const Handle& handle );

            /*!
             * @brief Obtains the device context associated to a window.
             */
        explicit DeviceContext ( const Window& window );

        explicit DeviceContext ( const string& device );
        explicit DeviceContext ( const Device& device );

        /* methods. */
    public:
            /*!
             * @brief Obtains the device context's handle.
             */
        const Handle& handle () const;

            /*!
             * @brief Set the pixel format for the device context.
             *
             * This can be done only once.
             */
        void set ( const PixelFormat& format );

            /*!
             * @brief Copy a rectangular region of pixels to another device.
             */
        void bitblt (
            const Rectangle& area,
            const DeviceContext& source,
            const Point& origin
            );

        void stretchblt (
            const Rectangle& darea,
            const DeviceContext& source,
            const Rectangle& sarea
            );

            /*|
             * @brief Obtains the device context's mapping mode.
             */
        MappingMode mapping () const;

            /*!
             * @brief Inverts the colors inside a region.
             */
        void invert ( const Region& region );

            /*!
             * @brief Paints the region with the current brush.
             */
        void fill ( const Region& region );

            /*!
             * @brief Paints the region with a given brush.
             */
        void fill ( const Region& region, const Brush& brush );

            /*!
             * @brief Paints a region's bounding box.
             */
        void frame (
            const Region& region, const Brush& brush, int hborder, int vborder
            );

            /*!
             * @brief Cancels any pending drawing operations.
             */
        void cancel ();

            /*!
             * @brief Renders a meta-file onto the device.
             */
        void play ( const Metafile& metafile );

            /*!
             * @brief Renders an enhanced meta-file onto the device.
             */
        void play (
            const EnhancedMetafile& metafile, const Rectangle& bounds
            );

            /*!
             * @brief Draws the nth image of an image list.
             */
        void draw (
            const ImageList& list, int image, const Point& position
            );

            /*!
             * @brief Writes text onto the window, starting at @a origin.
             */
        void write ( const Point& origin, const string& text );

        void put (
            DeviceCompatibleBitmap& target,
            const DeviceIndependantBitmap& source
            );

        void get (
            DeviceIndependantBitmap& target,
            const DeviceCompatibleBitmap& source
            );
    };

} }

#endif /* _w32_gdi_DeviceContext_hpp__ */
