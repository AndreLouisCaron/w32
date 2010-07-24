// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/enable_common_controls.hpp>

namespace w32 { namespace gdi {

    void enable_common_controls ()
    {
        ::INITCOMMONCONTROLSEX controls;
        ::ZeroMemory(&controls, sizeof(controls));
        controls.dwSize = sizeof(controls);
        controls.dwICC =
            ICC_STANDARD_CLASSES | ICC_WIN95_CLASSES | ICC_BAR_CLASSES;
        ::InitCommonControlsEx(&controls);
    }

} }
