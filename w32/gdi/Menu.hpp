#ifndef _w32_gdi_Menu_hpp__
#define _w32_gdi_Menu_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/Resource.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/gdi/Point.hpp>
#include <w32/gdi/Window.hpp>

// Window Menu Bar:
// See GetMenuBarInfo().
// See DrawMenuBar().

// Predefined Window Menus:
// See GetSystemMenu().
// See GetMenu().

// Menu Operations:
// See GetSubMenu().
// See GetMenuItemInfo().

namespace w32 { namespace gdi {

    class W32_GDI_EXPORT Menu
    {
        /* nested types. */
    public:
        typedef Reference< ::HMENU > Handle;

        class Item;

        /* class methods. */
    public:
        static Handle claim ( ::HMENU object );
        static Handle proxy ( ::HMENU object );

            /*!
             * @brief Creates a new popup menu.
             */
        static Menu popup ();

        /* data. */
    private:
        Handle myHandle;

      /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated menu.
             *
             * @see claim()
             * @see proxy()
             */
        explicit Menu ( const Handle& handle );

            /*!
             * @brief Loads a menu from an application resource.
             */
        explicit Menu ( const Resource& resource );

            /*!
             * @brief Creates a new dropdown menu, suited for a window.
             */
        Menu ();

      /* methods. */
    public:
            /*!
             * @brief Obtains the menu's handle.
             */
        const Handle& handle () const;

        uint popup ( const Window& window, const Point& point );
        void insert ( const Item& item, uint position );
        void insert ( const string& item, uint position, uint identifier );
    };

    class W32_GDI_EXPORT Menu::Item
    {
        /* nested types. */
    public:
        typedef ::MENUITEMINFOW Data;

        /* data. */
    protected:
        Data myData;

        /* construction. */
    public:
        Item ();
        explicit Item ( uint identifier );

        /* methods. */
    public:
        const Data& data () const;
        void identifier ( uint identifier );
        void text ( const string& text );
    };

} }

#endif /*  _w32_gdi_Menu_hpp__ */
