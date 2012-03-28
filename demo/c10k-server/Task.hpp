#ifndef _server_Task_hpp__
#define _server_Task_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net.hpp>
#include <w32.io.hpp>

namespace server {

    class Core;
    class Service;

    class Task
    {
    friend class Core;

        /* data. */
    private:
        Service& myService;

        /* construction. */
    public:
        Task ( Service& service );
        virtual ~Task ();

        /* methods. */
    public:
        Service& service ();
        Core& core ();

        virtual void acquired ();
        virtual void released ();

        virtual void abort () = 0;
        virtual void completed
            ( const w32::io::Transfer * transfer, w32::dword bytes ) = 0;
    };

}

#endif /* _c10kserver_Task_hpp__ */
