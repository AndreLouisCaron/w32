#ifndef _w32_gdi_desktop_hpp__
#define _w32_gdi_desktop_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Allows manipulation of the desktop window.
         *
         * It would be wise to use this carefully...
         */
    Window desktop ();

} }

#endif /* _w32_gdi_desktop */
