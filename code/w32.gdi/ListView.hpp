#ifndef _w32_gdi_ListView_hpp__
#define _w32_gdi_ListView_hpp__

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


