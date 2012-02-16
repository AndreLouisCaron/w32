#ifndef _w32_gdi_Static_hpp__
#define _w32_gdi_Static_hpp__

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

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

    class Bitmap;
    class Icon;

        /*!
         * @brief Control not responding to user input.
         */
    class Static :
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
