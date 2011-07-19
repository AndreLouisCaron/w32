#ifndef _w32_gdi_DeviceIndependantBitmap_hpp__
#define _w32_gdi_DeviceIndependantBitmap_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/gdi/Bitmap.hpp>
#include <w32/gdi/Size.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Wraps a system bitmap into which we can draw directly.
         */
    class DeviceIndependantBitmap :
        public Bitmap
    {
        /* nested types. */
    public:
        class Info;
        class Guard;

        /* construction. */
    public:
        explicit DeviceIndependantBitmap ( const Handle& handle );

            /*!
             * @brief Have the system allocate a bitmap.
             */
        DeviceIndependantBitmap (
            const DeviceContext& device, const Size& size, word depth
            );

            /*!
             * @brief Creates a display-compatible device independant bitmap.
             */
        DeviceIndependantBitmap ( const Size& size, word depth );

            /*!
             * @brief Creates a device independant copy of an existing bitmap.
             */
        DeviceIndependantBitmap (
            const Bitmap& image, const Size& size = Size(0,0)
            );

        /* methods. */
    public:
            /*!
             * @brief Obtains read/write access to the bitmap's pixel buffer.
             */
        void * buffer ();

            /*!
             * @brief Obtains read-only access to the bitmap's pixel buffer.
             */
        const void * buffer () const;

            /*!
             * @brief Saves the bitmap to a ".bmp" file.
             *
             * Although this function is not supported directly by the GDI
             * it is defined because it is so commonly needed and because
             * it can't really be written to be any better.
             *
             * @todo Move this to the \c Bitmap base class if possible.
             */
        void save ( const string& file ) const;
    };

        /*!
         * @brief Wraps general information about the bitmap.
         *
         * This structure contains more information than the
         * bitmap's information structure.
         */
    class DeviceIndependantBitmap::Info
    {
        /* nested types. */
    public:
        typedef ::DIBSECTION Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
            /*!
             * @brief Obtains info about an existing bitmap.
             */
        explicit Info ( const DeviceIndependantBitmap& bitmap );

        /* methods. */
    public:
            /*!
             * @brief Obtains the native representation.
             */
        Data& data ();

            /*!
             * @brief Obtains the native representation.
             */
        const Data& data () const;

            /*!
             * @brief Obtains the bitmap's width in pixels.
             */
        long width () const;

            /*!
             * @brief Obtains the bitmap's height in pixels.
             */
        long height () const;

            /*!
             * @brief Obtains the bitmap's depth in bits.
             */
        word depth () const;

            /*!
             * @brief Obtains a pointer to the image buffer.
             */
        void * buffer () const;
    };

        /*!
         * @brief Used to make sure GDI drawing is complete.
         */
    class DeviceIndependantBitmap::Guard :
        private w32::NotCopyable
    {
        /* construction. */
    public:
        Guard ( DeviceIndependantBitmap& bitmap );
    };

        /*!
         * @brief Bitmap loaded from a file.
         */
    class FileBitmap :
        public DeviceIndependantBitmap
    {
        /* nested types. */
    public:
        class Info;

        /* construction. */
    public:
        FileBitmap ( const string& path );

        /* overrides. */
    public:
        virtual void * buffer ();
        virtual const void * buffer () const;
    };

        /*!
         * @brief Wraps access to a system bitmap resource's information.
         */
    class FileBitmap::Info
    {
        /* nested types. */
    public:
        typedef ::BITMAP Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
            /*!
             * @brief Get info about a loaded object.
             */
        Info ( const FileBitmap& bitmap );

        /* methods. */
    public:
        Size size () const;
        word depth () const;
        void * buffer () const;
    };

} }

#endif /* _w32_gdi_DeviceIndependantBitmap_hpp__ */
