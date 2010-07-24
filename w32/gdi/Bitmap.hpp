#ifndef _w32_gdi_Bitmap_hpp__
#define _w32_gdi_Bitmap_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/Reference.hpp>

namespace w32 { namespace gdi {

    class Size;

    class DeviceContext;

        /*!
         * @brief Wraps a system managed bitmap.
         *
         * This is actually a wrong name though, as it does not contain only
         * monochrome pixels!
         */
    class W32_GDI_EXPORT Bitmap
    {
        /* nested types. */
    public:
        typedef Reference< ::HBITMAP > Handle;

        class Info;
        class Selection;

        /* class methods. */
    public:
        static Handle claim ( ::HBITMAP object );
        static Handle proxy ( ::HBITMAP object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Bitmap ( const Handle& handle );

        /* refinements. */
    public:
        const Handle& handle () const;
    };

        /*!
         * @brief Wraps general information about the bitmap.
         */
    class W32_GDI_EXPORT Bitmap::Info
    {
        /* nested types. */
    public:
        typedef ::BITMAPINFO Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
            /*!
             * @brief Obtains info about an existing bitmap.
             */
        Info ( const Bitmap& bitmap );

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

        Size size () const;

            /*!
             * @brief Obtains the bitmap's depth in bits.
             */
        word depth () const;
    };

        /*!
         * @brief Loads a bitmap as the current tool for a device context.
         */
    class W32_GDI_EXPORT Bitmap::Selection :
        private NotCopyable
    {
        /* data. */
    private:
        const ::HDC myDevice;
        const ::HGDIOBJ myPredecessor;

        /* construction. */
    public:
        Selection ( const DeviceContext& device, const Bitmap& bitmap );
        ~Selection ();
    };

} }

#endif /* _w32_gdi_Bitmap_hpp__ */
