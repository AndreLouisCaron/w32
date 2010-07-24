// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/gdi/MouseLeave.hpp>
#include <Windows.h>

namespace win32c { namespace gdi {

    MouseLeave::MouseLeave ()
        : Notification(WM_MOUSELEAVE,0,0)
    {}

    MouseLeave::MouseLeave ( ::WPARAM wparam, ::LPARAM lparam )
        : Notification(WM_MOUSELEAVE,wparam,lparam)
    {}

} }
