#ifndef _w32_gdi_loop_hpp__
#define _w32_gdi_loop_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/gdi/Event.hpp>
#include <w32/gdi/ThreadWindowsEvents.hpp>

namespace w32 { namespace gdi {

    W32_GDI_EXPORT wparam loop ();

    template<class Idle>
    wparam loop ( Idle idle )
    {
            // Make sure window responds.
        w32::gdi::Event message;
        ThreadWindowsEvents pump;
        while ( true )
        {
            if ( pump.peek(message) )
            {
                    // Exit the loop when requested to.
                if ( message.message() == WM_QUIT ) {
                    break;
                }
                message.translate();
                message.dispatch(); 
            }
            else {
                idle();
            }
        }
        return (message.wparam());
    }

} }

#endif /* _w32_gdi_loop_hpp__ */
