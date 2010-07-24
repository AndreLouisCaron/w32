#ifndef _win32c_gdi_KeyboardNotification_hpp__
#define _win32c_gdi_KeyboardNotification_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/gdi/Key.hpp>
#include <win32c/gdi/Notification.hpp>
#include <Windows.h>

namespace win32c { namespace gdi {

    class KeyboardNotification :
        public Notification
    {
        /* construction. */
    protected:
        KeyboardNotification ( ::UINT message )
            : Notification(message,0,0)
        {}

        KeyboardNotification ( ::UINT message, const Key& object )
            : Notification(message,0,0)
        { key(object); }

        KeyboardNotification
            ( ::UINT message, ::WPARAM wparam, ::LPARAM lparam )
            : Notification(message,wparam,lparam)
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

#endif /* _win32c_gdi_KeyboardNotification_hpp__ */
