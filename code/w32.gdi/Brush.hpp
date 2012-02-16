#ifndef _w32_gdi_Brush_hpp__
#define _w32_gdi_Brush_hpp__

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

namespace w32 { namespace gdi {

    class Color;
    class SystemColor;

        /*!
         * @brief Wraps a drawing tool used to fill regions.
         */
    class Brush
    {
        /* nested types. */
    public:
        typedef Reference< ::HBRUSH, void(*)(::HBRUSH) > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::HBRUSH object );
        static Handle proxy ( ::HBRUSH object );

        /* class data. */
    public:
        static const Brush null ();
        static const Brush white ();
        static const Brush lightGray ();
        static const Brush gray ();
        static const Brush darkGray ();
        static const Brush black ();

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated brush.
             *
             * @see claim()
             * @see proxy()
             */
        explicit Brush ( const Handle& handle );

            /*!
             * @brief Creates a new solid color brush.
             * @param color Color the brush will draw with.
             */
        explicit Brush ( const Color& color );

            /*!
             * @brief Obtains a system-color brush.
             */
        explicit Brush ( const SystemColor& color );

        /* methods. */
    public:
        const Handle& handle () const;
    };

} }

#endif /* _w32_gdi_Brush_hpp__ */
