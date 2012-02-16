#ifndef _w32_gdi_Tooltip_hpp__
#define _w32_gdi_Tooltip_hpp__

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
#include <w32.gdi/Icon.hpp>

namespace w32 { namespace gdi {

    class Rectangle;
    class Window;

        /*!
         * @brief Popup window used to display a hint about using something.
         */
    class Tooltip :
        public Control
    {
        /* nested types. */
    public:
        class Tool;
        class Icon;

        /* construction. */
    public:
        explicit Tooltip ( const Handle& handle );
        explicit Tooltip ( Window& window );

        /* methods. */
    public:
            /*!
             * @brief Adds a tip trigger.
             */
        void add ( const Tool& tool );

            /*!
             * @brief Removes a tip trigger.
             */
        void remove ( const Tool& tool );

            /*!
             * @brief Changes the tooltip's maximum width, in pixels.
             * @return Previous maximum width.
             */
        int maxTipWidth ( int width );

            /*!
             * @brief Allow the tooltip to be displayed.
             */
        void activate ();

            /*!
             * @brief Prevent the tooltip from being displayed.
             */
        void deactivate ();

            /*!
             * @brief Force the tooltip to be redrawn.
             */
        void update ();

            /*!
             * @brief Hide the tooltip.
             */
        void pop ();

            /*!
             * @brief Show the tooltip.
             */
        void popup ();

            /*!
             * @brief Obtain the current number of triggers.
             */
        int toolCount () const;

            /*!
             * @brief Change the tooltip's title.
             */
        void title ( const string& text );

            /*!
             * @brief Change the tooltip's title.
             */
        void title ( const string& text, const Icon& icon );

        #if (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_XPSP2)

            /*!
             * @brief Change the tooltip's title.
             */
        void title ( const string& text,
            const w32::gdi::Icon& icon = w32::gdi::Icon::none() );

        #endif /* (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_XPSP2) */
    };

        /*!
         * @brief Trigger for the tooltip to popup.
         */
    class Tooltip::Tool
    {
        /* nested types. */
    public:
        typedef ::TOOLINFOA Data;

        /* data. */
    private:
        Data myData;
        astring myCaption; // Hold a copy of the allocated memory.

        /* construction. */
    public:
            /*!
             * @brief Creates a tooltip for the entire window or control.
             */
        Tool ( const Window& window );
        Tool ( const Tool& other );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

            /*!
             * @brief Text displayed in the tooltip.
             */
        void caption ( const string& text );

            /*!
             * @brief Area of the window inside which the tool can be
             *     triggered.
             *
             * By default, this is the entire window's client area.
             */
        void area ( const Rectangle& bounds );

        /* operators. */
    public:
        Tool& operator= ( const Tool& other );
    };

        /*!
         * @brief Icon displayed next to the tooltip's title.
         */
    class Tooltip::Icon
    {
        /* nested types. */
    public:
        typedef int Value;

        /* class data. */
    public:
        static const Icon none ();
        static const Icon info ();
        static const Icon warning ();
        static const Icon error ();
        static const Icon infoLarge ();
        static const Icon warningLarge ();
        static const Icon errorLarge ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Icon ( Value value );

        /* methods. */
    public:
        Value value () const;
    };

} }

#endif /* _w32_gdi_Tooltip_hpp__ */
