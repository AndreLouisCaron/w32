#ifndef _w32_gdi_KeyReleased_hpp__
#define _w32_gdi_KeyReleased_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/KeyboardNotification.hpp>

namespace w32 { namespace gdi {

    class KeyReleased :
        public KeyboardNotification
    {
        /* construction. */
    public:
        explicit KeyReleased ( ::WPARAM wparam, ::LPARAM lparam )
            : KeyboardNotification(WM_KEYUP,wparam,lparam)
        {}
    };

} }

#endif /* _w32_gdi_KeyReleased_hpp__ */
