#ifndef _w32_gdi_ListBox_hpp__
#define _w32_gdi_ListBox_hpp__

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

// This should be refactored to multi-selection, multi-column,
// sorted-list, etc. classes.

#include "__configure__.hpp"
#include <w32.gdi/Control.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Control that displays a list of items.
         */
    class ListBox :
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
