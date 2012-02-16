#ifndef _w32_gdi_Region_hpp__
#define _w32_gdi_Region_hpp__

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
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    class Point;
    class Rectangle;
    class Size;

        /*!
         * @brief Describes an area of abitrary shape.
         */
    class Region
    {
        /* nested types. */
    public:
        typedef Reference< ::HRGN, void(*)(::HRGN) > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::HRGN object );
        static Handle proxy ( ::HRGN object );

            /*!
             * @brief Creates a rectangular area with square corners.
             */
        static Region rectangle ( const Rectangle& area );

            /*!
             * @brief Creates a rectangular area with round corners.
             */
        static Region rounded ( const Rectangle& area, const Size& size );

            /*!
             * @brief Creates an elliptic area.
             */
        static Region ellipse ( const Rectangle& area );

            /*!
             * @brief Creates a polygon-shaped area.
             * @note The polygon is presumed closed.
             */
        static Region polygon ( const Point * vertices, int count );

            /*!
             * @brief Creates a duplicate of a region.
             */
        static Region clone ( const Region& region );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Region ( const Handle& handle );

            /*!
             * @brief Creates an empty region.
             */
        Region ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the region's handle.
             */
        const Handle& handle () const;

            /*!
             * @brief Offset a region from it's current position.
             */
        void offset ( int x, int y );
        Rectangle box () const;
        bool contains ( const Point& point ) const;

        /* operators. */
    public:
            /*!
             * @brief Compute the difference between two regions.
             */
        Region& operator-= ( const Region& other );

            /*!
             * @brief Compute the union of two regions.
             */
        Region& operator|= ( const Region& other );

            /*!
             * @brief Compute the intersection of two regions.
             */
        Region& operator&= ( const Region& other );

            /*!
             * @brief Compute the exclusive union of two regions.
             */
        Region& operator^= ( const Region& other );

            /*!
             * @brief Checks if the regions are equal.
             */
        bool operator== ( const Region& other ) const;
    };

} }

#endif /* _w32_gdi_Region_hpp__ */
