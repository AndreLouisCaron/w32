#ifndef _w32_gdi_KeyboardNotification_hpp__
#define _w32_gdi_KeyboardNotification_hpp__

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
#include <w32.gdi/Key.hpp>

namespace w32 { namespace gdi {

    class KeyboardNotification
    {
        /* data. */
    private:
        ::UINT myCode;
        ::WPARAM myWparam;
        ::LPARAM myLparam;

        /* construction. */
    protected:
        KeyboardNotification ( ::UINT message )
            : myCode(message), myWparam(0), myLparam(0)
        {}

        KeyboardNotification ( ::UINT message, const Key& object )
            : myCode(message), myWparam(0), myLparam(0)
        { key(object); }

        KeyboardNotification
            ( ::UINT message, ::WPARAM wparam, ::LPARAM lparam )
            : myCode(message), myWparam(wparam), myLparam(lparam)
        {}

        /* methods. */
    public:
        Key key () const {
            return (Key(wparam()));
        }

        void key ( const Key& object ) {
            wparam(object.identifier());
        }

        ::BYTE repetitions () const {
            return (static_cast<::BYTE>(lparam() & 0x00007fff));
        }

        ::BYTE scan () const {
            return (static_cast<::BYTE>(lparam() & 0x007f8000));
        }

        bool extended () const {
            return ((lparam()&0x00800000) != 0);
        }

            /*!
             * @brief Indicates if the previous state (pressed or released) is
             *    different from the state indicated by this message.
             *
             * This is useful when tracking key repetitions, as you can know if
             * the user released the key between two series of repetitions.
             */
        bool changed () const {
            return ( ((lparam()&0x40000000) == 0) == pressed() );
        }

        bool released () const {
            return ((lparam()&0x80000000) != 0);
        }

        bool pressed () const {
            return ((lparam()&0x80000000) == 0);
        }
    };

} }

#endif /* _w32_gdi_KeyboardNotification_hpp__ */
