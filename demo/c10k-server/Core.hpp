#ifndef _server_Core_hpp__
#define _server_Core_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
