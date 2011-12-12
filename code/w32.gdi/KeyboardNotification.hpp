#ifndef _w32_gdi_KeyboardNotification_hpp__
#define _w32_gdi_KeyboardNotification_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
