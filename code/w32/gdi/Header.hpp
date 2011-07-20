#ifndef _w32_gdi_Header_hpp__
#define _w32_gdi_Header_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

    class Bitmap;
    class Rectangle;

    class Header :
        public Control
    {
        /* nested types. */
    public:
        class Item;

        /* construction. */
    public:
        explicit Header ( const Handle& handle );
        Header ( Window& parent, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief Obtains the number of items in the header.
             */
        int count () const;

            /*!
             * @brief Inserts a new item in the header.
             *
             * To insert an item at the end of the "item list", pass
             * count() or greater. To insert at the beginning, pass 0.
             *
             * @param index Index of the item before the new one.
             * @return Index of the new item.
             */
        int insert ( const Item& item, int index );

            /*!
             * @brief Removes the item at the given position.
             */
        void remove ( int index );
    };

    class Header::Item
    {
        /* nested types. */
    public:
        typedef ::HDITEMW Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Item ();

        /* methods. */
    public:
        const Data& data () const;
        void text ( const string& value );
        void size ( int value );
        void bitmap ( const Bitmap& image );
    };

} }

#endif /* _w32_gdi_Header_hpp__ */
