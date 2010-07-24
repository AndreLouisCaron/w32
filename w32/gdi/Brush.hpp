#ifndef _w32_gdi_Brush_hpp__
#define _w32_gdi_Brush_hpp__

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
    class SystemColor;

        /*!
         * @brief Wraps a drawing tool used to fill regions.
         */
    class W32_GDI_EXPORT Brush
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
