#ifndef _w32_gdi_ScrollBar_hpp__
#define _w32_gdi_ScrollBar_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>

// See SetScrollInfo().
// See ScrollWindowEx().
// See WM_VSCROLL, WM_HSCROLL.

namespace w32 { namespace gdi {

    class Rectangle;

    class W32_GDI_EXPORT ScrollBar :
        public Control
    {
        /* construction. */
    public:
        explicit ScrollBar ( const Handle& handle );
        ScrollBar ( Window& parent, const Rectangle& bounds );
    };

} }

#endif /* _w32_gdi_ScrollBar_hpp__ */
