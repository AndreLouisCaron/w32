#ifndef _w32_gdi_ListView_hpp__
#define _w32_gdi_ListView_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/gdi/Control.hpp>

namespace w32 { namespace gdi {

    class ImageList;

        /*!
         * @brief Control that displays a list of items.
         */
    class ListView :
        public Control
    {
        /* nested types. */
    public:
        class Column;
        typedef ::UINT size_type;

        /* construction. */
    public:
        explicit ListView ( const Handle& handle );
        ListView ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief Adds a new column at a given index.
             */
        int insert ( const Column& column, int index );

            /*!
             * @brief Obtains a column's properties.
             */
        Column column ( int index );

            /*!
             * @brief Changes a column's properties.
             */
        void column ( const Column& column, int index );

            /*!
             * @brief Changes the image list.
             */
        void largeIcons ( const ImageList& images );

            /*!
             * @brief Changes the image list.
             */
        void smallIcons ( const ImageList& images );

            /*!
             * @brief Changes the image list.
             */
        void states ( const ImageList& images );

            /*!
             * @brief Changes the background color.
             */
        void backgroundColor ( const Color& color );

            /*!
             * @brief Obtains the background color.
             */
        Color backgroundColor () const;

            /*!
             * @brief Obtains the number of items in the list.
             */
        size_type count () const;

            /*!
             * @brief Changes the color used for the item labels' text.
             */
        void textColor ( const Color& color );

            /*!
             * @brief Obtain the color used for the labels' text.
             */
        Color textColor () const;
    };

    class ListView::Column
    {
        /* nested types. */
    public:
        typedef ::LVCOLUMNW Data;

        /* data. */
    private:
        Data myData;
        string myCaption;

        /* construction. */
    public:
        Column ();
        Column ( const Data& data );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        void width ( int value );
        void caption ( const string& value );
    };

} }

#endif /* _w32_gdi_ListView_hpp__ */


