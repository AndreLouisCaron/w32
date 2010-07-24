#ifndef _w32_gdi_Region_hpp__
#define _w32_gdi_Region_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
