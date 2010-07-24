// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/gdi/MouseCapture.hpp>
#include <win32c/diagnostics/UncheckedError.hpp>

namespace win32c { namespace gdi {

    MouseCapture::MouseCapture Window& window )
        : myPredecessor(::SetCapture(window.handle().value()))
    {
    }

    MouseCapture::~MouseCapture ()
    {
        ::SetCapture(myPredecessor);
    }

    void MouseCapture::release ()
    {
        if ( ::ReleaseCapture() == 0 ) {
            UNCHECKED_WIN32C_ERROR(ReleaseCapture,::GetLastError);
        }
    }

} }
