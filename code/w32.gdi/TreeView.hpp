#ifndef _w32_gdi_TreeView_hpp__
#define _w32_gdi_TreeView_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32.gdi/Control.hpp>

namespace w32 { namespace gdi {

    class Color;
    class ImageList;
    class Rectangle;
    class Window;

        /*!
         * @brief Control used to display a hierarchy.
         */
    class TreeView :
        public Control
    {
        /* nested types. */
    public:
        class Item;
        class Insertion;

        typedef ::UINT size_type;

      /* class data. */
    public:
        static const Item root ();
        static const Item first ();
        static const Item last ();

        /* construction. */
    public:
        explicit TreeView ( const Handle& handle );
        TreeView ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
        Item insert ( const Insertion& insertion );

            /*!
             * @brief Expands a tree node, showing it's children.
             */
        void expand ( const Item& item );

            /*!
             * @brief Collapses a tree node, hiding it's children.
             */
        void collapse ( const Item& item );

            /*!
             * @brief Obtains the number of (displayed?) items in the tree.
             */
        size_type count () const;

            /*!
             * @brief Obtains an item's parent.
             */
        Item parent ( const Item& item ) const;

            /*!
             * @brief Changes the background color.
             */
        void backgroundColor ( const Color& color );

            /*!
             * @brief Obtains the background color.
             */
        Color backgroundColor () const;

            /*!
             * @brief Changes the text's color.
             */
        void textColor ( const Color& color );

            /*!
             * @brief Obtains the text's color.
             */
        Color textColor () const;

            /*!
             * @brief Changes the lines' color.
             */
        void lineColor ( const Color& color );

            /*!
             * @brief Obtains the lines' color.
             */
        Color lineColor () const;

        void images ( const ImageList& images );
        ImageList images () const;
    };

    class TreeView::Item
    {
        /* nested types. */
    public:
        typedef ::HTREEITEM Handle;

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Item ( Handle handle );

        /* methods. */
    public:
        Handle handle () const;
    };

    class TreeView::Insertion
    {
        /* nested types. */
    public:
        typedef ::TVINSERTSTRUCTW Data;

        /* data. */
    private:
        Data myData;
        string myCaption;

        /* construction. */
    public:
        Insertion ();
        Insertion ( Item& parent );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void caption ( const string& caption );
        void parent ( Item& parent );
        void children ( size_type children );
        void image ( size_type image );
        void images ( size_type normal, size_type selected );
    };

} }

#endif /* _w32_gdi_TreeView_hpp__ */
