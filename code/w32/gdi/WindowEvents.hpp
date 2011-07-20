#ifndef _win32c_gdi_WindowEvents_hpp__
#define _win32c_gdi_WindowEvents_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/gdi/EventQueue.hpp>

namespace win32c { namespace gdi {

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
        virtual bool next ( Event& event, const Filter& filter = anyEvent );
        virtual bool peek ( Event& event, const Filter& filter = anyEvent );
        virtual void post ( const Notification& notification );
    };

} }

#endif /* _win32c_gdi_WindowEvents_hpp__ */
