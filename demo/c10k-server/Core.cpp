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

#include "Core.hpp"
#include "Task.hpp"
#include "Service.hpp"
#include <algorithm>
#include <functional>

namespace {

    struct destroy {
        template<typename T> void operator()
            ( const T * object ) const { delete object; }
    };

}

namespace server {

    Core::Core ()
    {
            // Obtain number of processors on the system.
        const w32::size_t processors =
            w32::System().processors();
        
            // Create a worker thread per processor.
        myWorkers.reserve(processors);
        for ( w32::size_t i = 0; (i < processors); ++i )
        {
            const w32::mt::Thread worker
                (w32::mt::Thread::function<&Core::work>(), this);
            myWorkers.push_back(worker);
            myThreads |= worker.handle();
        }
        
            // Start accepting incoming connections.
        myListener.reset(new w32::mt::Thread(
            w32::mt::Thread::function<&Core::wait>(), this));
        myThreads |= myListener->handle();
    }

    Core::~Core ()
    {
            // Stop the listener thread.
        myShutdown.set();
        
            // Notify clients of intention to close connetions.
        std::for_each(
            myTasks.begin(), myTasks.end(), std::mem_fun(&Task::abort));
        
            // Make all worker threads un-block.
        for ( std::size_t i = 0; (i < myWorkers.size()); ++i ) {
            myPort.put(0, 0, 0);
        }
        
            // Wait for all threads to complete.
        w32::Waitable::all(myThreads);
        
            // Force-close any remaining connections!
        std::for_each(myTasks.begin(), myTasks.end(), destroy());
    }

    void Core::ready ()
    {
            // Allow threads to go ahead!
        myStartup.set();
    }

    bool Core::closing () const
    {
        return (myShutdown.test());
    }

    void Core::bind( w32::net::StreamSocket& stream, Task& task )
    {
        myPort.bind(stream, &task);
    }

    void Core::bind( w32::io::Stream& stream, Task& task )
    {
        myPort.bind(stream, &task);
    }

    void Core::add ( Service * service )
    {
    const w32::mt::CriticalSection::Lock _(myLock);
        myServices.push_back(service);
    }

    void Core::del ( Service * service )
    {
    const w32::mt::CriticalSection::Lock _(myLock);
        myServices.erase(std::find(
            myServices.begin(), myServices.end(), service));
    }

    void Core::add ( Task * task )
    {
    const w32::mt::CriticalSection::Lock _(myLock);
        
            // Add the task.
        myTasks.insert(task);
    }

    void Core::del ( Task * task )
    {
    const w32::mt::CriticalSection::Lock _(myLock);
        
            // Remove the task.
        myTasks.erase(task);
    }

    w32::dword Core::work ( void * context )
    try
    {
        Core& core = *reinterpret_cast< Core* >(context);
        
            // Standby while startup completes.
        core.myStartup.wait();
        
        do {
                // Wait for something to show up in the queue.
            w32::dword size = 0;
            w32::ulongptr task = 0;
            w32::io::Transfer * transfer = 0;
            core.myPort.get(size, task, transfer);
            
                // The core sends empty messages to unblock threads,
                // forcing test of the 'core.closing()' condition.
            if ( task != 0 ) {
                    // Something actually finished, get the show on the road!
                reinterpret_cast<Task*>(task)->completed(transfer, size);
            }
         }
             // Note: because of "connection aborted" possibility, using
             // "task == 0" test does not necessarily indicate server
             // shutdown.  Rely on explicit, specific test instead!
         while ( !core.closing() );
         
         std::cout << "  (( over and out. ))" << std::endl;

         return (0);
    }
    catch ( const w32::Error& error )
    {
        std::cerr << "  (( error: '" << error << ".'! ))" << std::endl;
        return (1);
    }

    w32::dword Core::wait ( void * context )
    try
    {
        Core& core = *reinterpret_cast<Core*>(context);
        
            // Standby while startup completes.
        core.myStartup.wait();
        
            // Start listening for incoming connections.
        const w32::net::Timespan timeout(0, 10*1000);
        w32::net::Host host(w32::computername());
        w32::net::ipv4::Address address
            (host.address<w32::net::ipv4::Address>(0));
        std::cout << "  (( host @ '" << address << "'. ))" << std::endl;
        
            // Open a listening socket for each service.
        std::vector< w32::net::tcp::Listener > listeners;
        for ( std::size_t i = 0; (i < core.myServices.size()); ++i )
        {
            const w32::net::uint16 port = core.myServices[i]->port();
            listeners.push_back(w32::net::tcp::Listener(
                w32::net::ipv4::EndPoint(address, port)));
            std::cout << "  (( opened port " << (w32::uint16)port << ". ))" << std::endl;
        }
        
        do {
                // Repeatedly admit people in!
            w32::net::Set readers;
            for ( std::size_t i = 0; (i < core.myServices.size()); ++i ) {
                readers.add(listeners[i]);
            }
            if ( w32::net::select(readers,timeout) )
            {
                std::cout
                    << "  (( incoming connection on port ";
                
                    // Lookup which services have pending connections.
                for ( std::size_t i = 0; (i < listeners.size()); ++i )
                {
                    if ( !readers.contains(listeners[i]) ) {
                        continue;
                    }
                    
                    Service *const service = core.myServices[i];
                    
                    std::cout
                        << service->port() << ". ))" << std::endl;
                    
                        // Accept input connection and create client.
                    w32::net::ipv4::EndPoint peer;
                    w32::net::tcp::Stream stream(listeners[i], peer);
                    core.add(service->connected(stream, peer));
                }
            }
        }
             // Listen for server shutdown notifications too!
        while ( !core.closing() );
        
        std::cout << "  (( over and out. ))" << std::endl;

        return (0);
    }
    catch ( const w32::Error& error )
    {
        std::cerr << "  (( error: '" << error << ".'! ))" << std::endl;
        return (1);
    }

}
