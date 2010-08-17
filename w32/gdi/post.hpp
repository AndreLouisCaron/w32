#ifndef _w32_gdi_Post_hpp__
#define _w32_gdi_Post_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace mt {

    class Thread;

} }

namespace w32 { namespace gdi {

    class Message;
    class Window;

    W32_GDI_EXPORT void post
        ( Window& window, const Message& message );
    W32_GDI_EXPORT void post ( const Message& message );
    W32_GDI_EXPORT void post
        ( mt::Thread& thread, const Message& message );

} }

#endif /* _w32_gdi_Post_hpp__ */
