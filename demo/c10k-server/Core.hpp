#ifndef _server_Core_hpp__
#define _server_Core_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net.hpp>
#include <w32.hpp>
#include <w32.io.hpp>
#include <w32.mt.hpp>
#include <vector>
#include <set>

namespace server {

    class Task;
    class Service;

    class Core
    {
        /* data. */
    private:
        std::vector<Service*> myServices;
        std::auto_ptr< w32::mt::Thread > myListener;

        std::set< Task* > myTasks;

        w32::io::CompletionPort myPort;
        w32::Waitable::Set myThreads;
        std::vector< w32::mt::Thread > myWorkers;
        w32::mt::ManualResetEvent myStartup;
        w32::mt::ManualResetEvent myShutdown;
        w32::mt::CriticalSection myLock;

        /* construction. */
    public:
        Core ();
        ~Core ();

        /* methods. */
    public:
        void ready ();

        void bind ( w32::net::StreamSocket& stream, Task& task );
        void bind ( w32::io::Stream& stream, Task& task );
        bool closing () const;

        void add ( Service * service );
        void del ( Service * service );

        void add ( Task * task );
        void del ( Task * task );

        /* class methods. */
    private:
        static w32::dword wait ( void * context );
        static w32::dword work ( void * context );
    };

}

#endif /* _server_Core_hpp__ */
