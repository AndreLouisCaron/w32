#ifndef _win32c_gdi_MouseNotification_hpp__
#define _win32c_gdi_MouseNotification_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/gdi/Point.hpp>
#include <win32c/gdi/Notification.hpp>
#include <Windows.h>

namespace win32c { namespace gdi {

    class MouseNotification :
        public Notification
    {
        /* construction. */
    protected:
        MouseNotification ( ::UINT message )
            : Notification(message,0,0)
        {}

        MouseNotification ( ::UINT message, const Point& point )
            : Notification(message,0,0)
        { cursor(point); }

        MouseNotification (  ::UINT message, ::WPARAM wparam, ::LPARAM lparam )
            : Notification(message,wparam,lparam)
        {}

        /* methods. */
    public:
        Point cursor () const {
            return (Point(LOWORD(lparam()),HIWORD(lparam())));
        }

        void cursor ( const Point& point ) {
            wparam(MAKEWPARAM(point.x(),point.y()));
        }
    };

} }

#endif /* _win32c_gdi_MouseNotification_hpp__ */
