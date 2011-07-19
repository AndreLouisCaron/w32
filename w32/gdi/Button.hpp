#ifndef _w32_gdi_Button_hpp__
#define _w32_gdi_Button_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>
#include <w32/gdi/Message.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

    class Bitmap;
    class Icon;

    // BS_TYPEMASK is ..
    //   1) BS_PUSHBUTTON  and BS_DEFPUSHBUTTON
    //   2) BS_CHECKBOX    and BS_AUTOCHECKBOX
    //   3) BS_RADIOBUTTON and BS_AUTORADIOBUTTON
    //   4) BS_3STATE      and BS_AUTO3STATE
    // See also "Command link"-type buttons.

    class Button :
        public Control
    {
        /* class methods. */
    public:
        typedef Notification< Button, BN_CLICKED > Click;
        typedef Notification< Button, BN_DBLCLK > DoubleClick;
        typedef Notification< Button, BN_PAINT > Paint;
        typedef Notification< Button, BN_PUSHED > Push;
        typedef Notification< Button, BN_UNPUSHED > Pop;
        typedef Notification< Button, BN_UNPUSHED > Disable;
        typedef Notification< Button, BN_SETFOCUS > Focus;
        typedef Notification< Button, BN_KILLFOCUS > Ignore;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated button control.
             *
             * @see claim()
             * @see proxy()
             */
        explicit Button ( const Handle& handle );

            /*!
             * @brief Creates a new button control on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        Button ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            // Button styles...
        void checkbox ();
        void radio ();
        void push ();

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

            /*!
             * @brief Indicates if the push button is pressed.
             */
        bool pushed () const;

            /*!
             * @brief Indicates if the push button is not pressed.
             */
        bool poped () const;

            /*!
             * @brief Verifies if the radio button or check box is checked.
             */
        bool checked () const;

            /*!
             * @brief Verifies that the radio button or check box is not checked.
             */
        bool clear () const;
    };

} }

#endif /* _w32_gdi_Button_hpp__ */
