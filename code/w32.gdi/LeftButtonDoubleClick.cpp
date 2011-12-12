// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/LeftButtonDoubleClick.hpp>

namespace w32 { namespace gdi {

    LeftButtonDoubleClick::LeftButtonDoubleClick ( const Point& point )
        : MouseNotification(WM_LBUTTONDBLCLK,MAKEWPARAM(point.x(),point.y()),0)
    {}

    LeftButtonDoubleClick::LeftButtonDoubleClick
        ( ::WPARAM wparam, ::LPARAM lparam )
        : MouseNotification(WM_LBUTTONDBLCLK,wparam,lparam)
    {}

} }
