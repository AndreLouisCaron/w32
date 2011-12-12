#ifndef _w32_gdi_MouseNotification_hpp__
#define _w32_gdi_MouseNotification_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.gdi/Point.hpp>
#include <w32.gdi/Notification.hpp>

namespace w32 { namespace gdi {

    class MouseNotification
    {
        /* data. */
    private:
        ::UINT myCode;
        ::WPARAM myWparam;
        ::LPARAM myLparam;

        /* construction. */
    protected:
        MouseNotification ( ::UINT code )
            : myCode(code), myWparam(0), myLparam(0)
        {}

        MouseNotification ( ::UINT code, const Point& point )
            : myCode(code), myWparam(0), myLparam(0)
        { cursor(point); }

        MouseNotification (  ::UINT code, ::WPARAM wparam, ::LPARAM lparam )
            : myCode(code), myWparam(wparam), myLparam(lparam)
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

#endif /* _w32_gdi_MouseNotification_hpp__ */
