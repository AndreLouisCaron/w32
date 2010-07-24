#ifndef _w32_gdi_Tooltip_hpp__
#define _w32_gdi_Tooltip_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/gdi/Control.hpp>
#include <w32/gdi/Icon.hpp>

namespace w32 { namespace gdi {

    class Rectangle;
    class Window;

        /*!
         * @brief Popup window used to display a hint about using something.
         */
    class W32_GDI_EXPORT Tooltip :
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
    class W32_GDI_EXPORT Tooltip::Tool
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
    class W32_GDI_EXPORT Tooltip::Icon
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
