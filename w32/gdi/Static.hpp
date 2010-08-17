#ifndef _w32_gdi_Static_hpp__
#define _w32_gdi_Static_hpp__

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

    class Bitmap;
    class Icon;

        /*!
         * @brief Control not responding to user input.
         */
    class W32_GDI_EXPORT Static :
        public Control
    {
        /* nested types. */
    public:
        typedef Notification< Static, STN_CLICKED > Click;
        typedef Notification< Static, STN_DBLCLK > DoubleClick;
        typedef Notification< Static, STN_ENABLE > Enable;
        typedef Notification< Static, STN_DISABLE > Disable;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated static control.
             *
             * @see claim()
             * @see proxy()
             */
        explicit Static ( const Handle& handle );

        Static ( const Rectangle& bounds );

            /*!
             * @brief Creates a new static control on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        Static ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief Makes the content a label, showing @a text.
             */
        void text ( const string& text );

            /*!
             * @brief Obtains the content of the label.
             */
        string text () const;

            /*!
             * @brief Makes the content an image box, showing @a bitmap.
             */
        void bitmap ( const Bitmap& bitmap );

            /*!
             * @brief Obtains the content of the image box.
             */
        Bitmap bitmap () const;

            /*!
             * @brief Makes the content an icon box, showing @a icon.
             */
        void icon ( const Icon& icon );

            /*!
             * @brief Obtains the content of the icon box.
             */
        Icon icon () const;
    };

} }

#endif /* _w32_gdi_Static_hpp__*/
