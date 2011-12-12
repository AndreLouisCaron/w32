#ifndef _w32_gdi_ComboBox_hpp__
#define _w32_gdi_ComboBox_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Control.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Edit box & list box.
         */
    class ComboBox :
        virtual public Control
    {
        /* nested types. */
    public:
        typedef Notification< ComboBox, CBN_SELCHANGE > Select;
        typedef Notification< ComboBox, CBN_DBLCLK > DoubleClick;
        typedef Notification< ComboBox, CBN_SETFOCUS > Focus;
        typedef Notification< ComboBox, CBN_KILLFOCUS > Ignore;
        typedef Notification< ComboBox, CBN_EDITCHANGE > Change;
        typedef Notification< ComboBox, CBN_EDITUPDATE > Update;
        typedef Notification< ComboBox, CBN_DROPDOWN > Drop;
        typedef Notification< ComboBox, CBN_SELENDOK > Ok;
        typedef Notification< ComboBox, CBN_SELENDCANCEL > Cancel;

        /* methods. */
    public:
        typedef int size_type;

            /*!
             * @brief Index indicating no selection.
             */
        static size_type none ();

        /* construction. */
    public:
        explicit ComboBox ( const Handle& handle );
        ComboBox ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief Sets the content of the edit box.
             */
        void text ( const string& text );

            /*!
             * @brief Obtains the content of the edit box.
             */
        string text () const;

            /*!
             * @brife Obtains the number of items in the list box.
             */
        size_type size () const;

            /*!
             * @brief Appends an item to the list box.
             *
             * @param item Value to append.
             * @return Index of the inserted item.
             *
             * @see insert(), del(), clear(), size()
             */
        size_type append ( const string& item );

            /*!
             * @brief Inserts an item at a specific position in the list.
             *
             * @param item Value to insert.
             * @param index Position where the item will be inserted. The item
             *   at this position is lowered one position (all others follow).
             *
             * @warning This does not cause automagically sorted combo boxes to
             *   be sorted. When using those, you should consider using add().
             */
        void insert ( const string& item, size_type index );

            /*!
             * @brief Removes an item to the list box.
             * @param item Item index.
             */
        void del ( size_type item );

            /*!
             * @brief Removes all items from the list box.
             */
        void clear ();

            /*!
             * @brief Obtains the currently selected item.
             * @see select(), unselect().
             */
        size_type selection () const;

            /*!
             * @brief Changes the selection.
             */
        void select ( size_type item );

            /*!
             * @brief Changes the selection to none().
             */
        void unselect ();
    };

} }

#endif /* _w32_gdi_ComboBox_hpp__ */
