#ifndef _w32_gdi_TreeView_hpp__
#define _w32_gdi_TreeView_hpp__

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
