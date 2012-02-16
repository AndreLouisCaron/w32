#ifndef _w32_gdi_Pen_hpp__
#define _w32_gdi_Pen_hpp__

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

        /*!
         * @brief Wraps a drawing tool used to draw lines.
         */
    class Pen
    {
        /* nested types. */
    public:
        typedef Reference< ::HPEN, void(*)(::HPEN) > Handle;

        class Style
        {
            /* nested types. */
        public:
            typedef int Value;

            /* class data. */
        public:
            static Style solid ();
            static Style dash ();
            static Style null ();

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            Style ( Value value );

            /* methods. */
        public:
            operator Value () const;
        };

        /* class methods. */
    public:
        static Handle claim ( ::HPEN object );
        static Handle proxy ( ::HPEN object );

        /* class data. */
    public:
        static const Pen null ();
        static const Pen white ();
        static const Pen black ();

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated pen.
             *
             * @see claim()
             * @see proxy()
             */
        explicit Pen ( const Handle& handle );

            /*!
             * @brief Creates a new logical pen.
             *
             * @param color Color used to draw with.
             * @param width Line width, in logical units. If this is 0, the line
             *   is a single pixel wide. If this is greater then one, the dash
             *   style is overriden by the solid style.
             * @param style Line style.
             *
             * @see MappingMode
             */
        explicit Pen (
            const Color& color, int width, const Style& style=Style::solid() );

        /* refinements. */
    public:
        const Handle& handle () const;
    };

} }

#endif /* _w32_gdi_Pen_hpp__ */
