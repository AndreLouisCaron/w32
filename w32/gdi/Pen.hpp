#ifndef _w32_gdi_Pen_hpp__
#define _w32_gdi_Pen_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
