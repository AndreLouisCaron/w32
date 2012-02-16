#ifndef _w32_gdi_TabControl_hpp__
#define _w32_gdi_TabControl_hpp__

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
#include <w32.gdi/Control.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

    class ImageList;
    class Rectangle;
    class Tooltip;

        /*!
         * @brief Control used to overlap groups of child controls.
         */
    class TabControl :
        public Control
    {
        /* nested types. */
    public:
        class Tab;

        /* construction. */
    public:
        explicit TabControl ( const Handle& handle );
        TabControl ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
        void insert ( const Tab& tab, int index );

        void clear ();
        void remove ( int index );
        int selection () const;
        int selection ( int index );
        ImageList images () const;
        void images ( const ImageList& list );
        Tab tab ( int index ) const;
        void tab ( int index, const Tab& tab );

        int tabs () const;
        int rows () const;

        Tooltip tip () const;
        void tip ( const Tooltip& help );

            /*!
             * @brief Removes an image from the image list and updates the tabs'
             *     image indexes.
             * @param index Index of the item to remove.
             */
        void removeImage ( int index );
    };

    class TabControl::Tab
    {
        /* nested types. */
    public:
        typedef ::TC_ITEMW Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Tab ();
        Tab ( const Data& data );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void caption ( const string& text );
    };

} }

#endif /* _w32_gdi_TabControl_hpp__ */
