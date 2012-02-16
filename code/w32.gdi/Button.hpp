#ifndef _w32_gdi_Button_hpp__
#define _w32_gdi_Button_hpp__

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
#include <w32.gdi/Control.hpp>
#include <w32.gdi/Message.hpp>

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
