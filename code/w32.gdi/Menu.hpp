#ifndef _w32_gdi_Menu_hpp__
#define _w32_gdi_Menu_hpp__

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
#include <w32/Reference.hpp>
#include <w32/Resource.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32.gdi/Point.hpp>
#include <w32.gdi/Window.hpp>

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

    class Menu
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

    class Menu::Item
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
