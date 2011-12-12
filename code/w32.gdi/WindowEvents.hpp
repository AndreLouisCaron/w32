#ifndef _w32_gdi_WindowEvents_hpp__
#define _w32_gdi_WindowEvents_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.gdi/EventQueue.hpp>
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

    class WindowEvents :
        public EventQueue
    {
        /* data. */
    private:
        const Window& myWindow;

        /* construction. */
    public:
        WindowEvents ( const Window& window );

        /* methods. */
    public:
        const Window& window () const;

        /* overrides. */
    public:
        virtual bool next ( Event& event, Filter filter = Filter::any() );
        virtual bool peek ( Event& event, Filter filter = Filter::any() );
        virtual void post ( const Message& message );
    };

} }

#endif /* _w32_gdi_WindowEvents_hpp__ */
