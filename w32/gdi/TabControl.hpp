#ifndef _w32_gdi_TabControl_hpp__
#define _w32_gdi_TabControl_hpp__

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

    class ImageList;
    class Rectangle;
    class Tooltip;

        /*!
         * @brief Control used to overlap groups of child controls.
         */
    class W32_GDI_EXPORT TabControl :
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

    class W32_GDI_EXPORT TabControl::Tab
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
