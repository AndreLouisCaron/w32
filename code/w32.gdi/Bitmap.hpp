#ifndef _w32_gdi_Bitmap_hpp__
#define _w32_gdi_Bitmap_hpp__

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
    class Bitmap
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
    class Bitmap::Info
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
    class Bitmap::Selection :
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
