#ifndef _w32_gdi_ListBox_hpp__
#define _w32_gdi_ListBox_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

// This should be refactored to multi-selection, multi-column,
// sorted-list, etc. classes.

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Control that displays a list of items.
         */
    class W32_GDI_EXPORT ListBox :
        public Control
    {
        /* nested types. */
    public:
        typedef Notification< ListBox, LBN_SELCHANGE > Select;
        typedef Notification< ListBox, LBN_SELCANCEL > Cancel;
        typedef Notification< ListBox, LBN_DBLCLK > DoubleClick;
        typedef Notification< ListBox, LBN_SETFOCUS > Focus;
        typedef Notification< ListBox, LBN_KILLFOCUS > Ignore;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated listbox control.
             *
             * @see claim()
             * @see proxy()
             */
        explicit ListBox ( const Handle& handle );

            /*!
             * @brief Creates a new listbox control on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        ListBox ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief Adds the string to the list box.
             *
             * If the list box has the sort style, the strings will
             * be sorted; if not, it will be appended at the end of the
             * list.
             */
        int add ( const string& entry );

            /*!
             * @brief Inserts the string at a specific position.
             *
             * The list box will not be sorted, even if the list box
             * has the sort style.
             */
        int insert ( const string& entry, int position );

            /*!
             * @brief Adds a string at the end of the list.
             *
             * The list box will not be sorted, even if the list box
             * has the sort style.
             */
        int append ( const string& entry );

            /*!
             * @brief Removes the string at a given position.
             */
        int remove ( int position );

            /*!
             * @brief Returns the index of the selected item.
             *
             * It no item is selected, this will return -1.
             */
        int selection () const;

            /*!
             * @brief Returns the number of selected items.
             */
        int selectionCount () const;

            /*!
             * @brief Returns an array of selection item indexes.
             *
             * @param items Pointer to an array of integers.
             * @param maximum Maximum number of items.
             * @return The actual number of selected items.
             */
        int selection ( int * items, int maximum ) const;

            /*!
             * @brief Selects the item at a given position.
             */
        void selection ( int position );

            /*!
             * @brief Selects an item in a multiple selection.
             */
        void select ( int position );

            /*!
             * @brief Selects an item in a multiple selection.
             */
        void unselect ( int position );

            /*!
             * @brief Selects all items.
             */
        void selectAll ();

            /*!
             * @brief Clears the entire selection.
             */
        void clearSelection ();

            /*!
             * @brief Reserves memory for extra items.
             *
             * This is useful when you want to insert many more elements
             * in the list box.
             *
             * @param count The number of extra items you wish to insert.
             * @param lengths The number of bytes each item requires.
             */
        int reserve ( int count, int lengths );

            /*!
             * @brief Removes all items from the list.
             */
        void clear ();
    };

} }


#endif /* _w32_gdi_ListBox_hpp__ */
