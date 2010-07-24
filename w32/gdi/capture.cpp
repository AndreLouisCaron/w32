// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/capture.hpp>
#include <w32/gdi/DeviceContext.hpp>
#include <w32/gdi/DeviceIndependantBitmap.hpp>
#include <w32/gdi/Rectangle.hpp>

namespace w32 { namespace gdi {

    w32::gdi::DeviceIndependantBitmap capture
        ( const w32::gdi::DeviceContext& source, const Rectangle& bounds )
    {
            // Create an auxiliary device context for capture.
        w32::gdi::DeviceContext destination =
            w32::gdi::DeviceContext::compatible(source);
        
            // Create a buffer to receive the screen capture.
        w32::gdi::DeviceIndependantBitmap capture(source, bounds.span(), 24);
        
            // Take the screen capture.
        { w32::gdi::Bitmap::Selection _(destination, capture);
            destination.bitblt(bounds, source, w32::gdi::Point());
        }
        
        return (capture);
    }

} }
