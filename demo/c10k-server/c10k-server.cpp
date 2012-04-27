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

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

namespace {

    // TODO: track part of input buffer containing data!
    // TODO: verify use of overlapped structure...

        // Background thread execution functions.
    w32::dword wait ( void * context );
    w32::dword work ( void * context );

        // Server-side per-connection information.
    class Client
    {
        static const w32::size_t GBufSize = 1024;
        static const w32::size_t PBufSize = 1024;
        char myGBuffer[GBufSize]; w32::io::Transfer myGet;
        char myPBuffer[PBufSize]; w32::io::Transfer myPut;
        w32::net::tcp::Stream myStream;
    public:
        Client ( const w32::net::tcp::Stream& stream )
            : myStream(stream)
        {
        }

        ~Client () {
            close();
        }

        void close () {
            myStream.shutdown(w32::net::Socket::Shutdown::both());
        }

            // Initiate asynchronous transfer.
        void get () {
            w32::net::Buffer buffer(myGBuffer, GBufSize);
            myStream.get(buffer, myGet);
        }
        void put ( w32::dword bytes ) {
            w32::net::Buffer buffer(myPBuffer, bytes);
            myStream.put(buffer, myPut);
        }

            // Asynchronous transfer completion notification.
        void operator() ( const w32::io::Transfer& transfer, w32::dword bytes )
        {
            // TODO: do something with transfer completion information.
            
                // Take action depending on type of transfer.
            if ( &transfer == &myGet )
            {
                std::cerr
                    << "'recv()'ed " << bytes << " bytes."
                    << std::endl;
                
                    // Replicate data to client.
                std::memcpy(myPBuffer, myGBuffer, bytes);
                put(bytes);
            }
            else
            {
                std::cerr
                    << "'send()'ed " << bytes << " bytes."
                    << std::endl;
                
                    // Request more input!
                get();
            }
        }
    };

        // Server-global data.
    class Server
    {
        w32::Waitable::Set myThreads;
        w32::mt::ManualResetEvent myStartup;
        w32::mt::ManualResetEvent myShutdown;
        std::vector< w32::mt::Thread > myWorkers;
        std::auto_ptr< w32::mt::Thread > myListener;
        w32::io::CompletionPort myPort;
        std::vector< Client* > myConnections;
        w32::mt::CriticalSection myConnectionLock;
    public:
        Server ()
        {
            const w32::size_t processors = w32::System().processors();
            myWorkers.reserve(processors);
            
                // Create a worker thread per processor.
            for ( w32::size_t i = 0; (i < processors); ++i )
            {
                const w32::mt::Thread worker
                    (w32::mt::Thread::function<&work>(), this);
                myWorkers.push_back(worker);
                myThreads |= worker.handle();
            }
            
                // Start accepting incoming connections.
            myListener.reset(new w32::mt::Thread(
                w32::mt::Thread::function<&wait>(), this));
            myThreads |= myListener->handle();
            
                // Allow threads to go ahead!
            myStartup.set();
        }

        ~Server ()
        {
                // Stop the listener thread.
            myShutdown.set();
            
                // Notify clients of intention to close connetions.
            for ( std::size_t i = 0; (i < myConnections.size()); ++i ) {
                myConnections[i]->close();
            }
            
                // Make all worker threads un-block.
            for ( std::size_t i = 0; (i < myWorkers.size()); ++i ) {
                myPort.unblock_consumers();
            }
            
                // Wait for all threads to complete.
            w32::Waitable::all(myThreads);
            
                // Force-close any remaining connections!
            for ( std::size_t i = 0; (i < myConnections.size()); ++i ) {
                delete myConnections[i];
            }
        }

            // Wait for server initialization to finish!
        void standby () const { myStartup.wait(); }

            // Check if shutdown requested!
        bool closing () const { return (myShutdown.test()); }

        w32::io::CompletionPort& port () { return (myPort); }

            // Synchronize access before using, please!
        std::vector< w32::mt::Thread >& workers () { return (myWorkers); }
        std::vector< Client* >& connections () { return (myConnections); }

        void add ( Client * connection )
        {
        const w32::mt::CriticalSection::Lock _(myConnectionLock);
            myConnections.push_back(connection);
        }

        void del ( Client * connection )
        {
        const w32::mt::CriticalSection::Lock _(myConnectionLock);
            myConnections.erase(std::find(
                myConnections.begin(), myConnections.end(), connection));
        }
    };

    w32::dword wait ( void * context )
    try
    {
        Server& server = *reinterpret_cast< Server* >(context);
        
            // Wait for server initialization to finish!
        server.standby();
        
            // Start listening for incoming connections.
        w32::net::Host host(w32::computername());
        w32::net::ipv4::Address address
            (host.address<w32::net::ipv4::Address>(0));
        w32::net::tcp::Listener listener(
            w32::net::ipv4::EndPoint(address,4321));
        w32::mt::ManualResetEvent event;
        listener.select(event, w32::net::Event::accept());
        
        do {
                // Repeatedly admit people in!
            if ( event.wait(w32::Timespan(100)) )
            {
                std::cout
                    << "Listener: event occured!"
                    << std::endl;
                
                const w32::net::Events events(listener, event);
                if ( events & w32::net::Event::accept() )
                {
                    std::cout
                        << "Listener: accepting connection!"
                        << std::endl;
                    
                        // Accept input connection and create client.
                    w32::net::tcp::Stream stream(listener);
                    Client *const client = new Client(stream);
                    server.add(client);
                    server.port().bind(
                        stream, reinterpret_cast< w32::ulongptr >(client));
                    
                        // Be ready to receive data at all times!
                    client->get();
                }
            }
        }
             // Listen for server shutdown notifications too!
        while ( !server.closing() );
        
        std::cout << "Listener: over and out!" << std::endl;

        return (0);
    }
    catch ( const w32::Error& error )
    {
        std::cerr << "Listener: " << error << "!" << std::endl;

        return (1);
    }

    w32::dword work ( void * context )
    try
    {
        Server& server = *reinterpret_cast< Server* >(context);
        
            // Wait for server initialization to finish!
        server.standby();
        
        do {
                // Wait for something to show up in the queue.
            w32::dword bytes = 0;
            w32::ulongptr key = 0;
            w32::io::Transfer * transfer = 0;
            server.port().next(bytes, key, transfer);
            
                // Efficient recovery of connection information! :-)
            Client *const client = reinterpret_cast< Client* >(key);
            
                // Something to process?
            if ( client == 0 ) { continue; }
            
                 // Received client-end shutdown?
            if ( bytes == 0 )
            {
                std::cout
                    << "Worker: client disconnected! :-("
                    << std::endl;
                server.del(client); delete client; continue;
            }
            
                // Something actually finished, get the show on the road!
            (*client)(*transfer, bytes);
         }
             // Note: because of "connection aborted" possibility, using
             // "client == 0" test does not necessarily indicate server
             // shutdown. Rely on explicit, specific test instead!
         while ( !server.closing() );
         
         std::cout << "Worker: over and out!" << std::endl;

         return (0);
    }
    catch ( const w32::Error& error )
    {
        std::cerr << "Worker: " << error << "!" << std::endl;

        return (1);
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
    const w32::net::Context _;
        
            // Configure?
        // ...
        
            // Execute server!
        ::Server server;
        std::cout << "Up and running!" << std::endl;
        
            // Don't stop listening to the user because the server is running.
        for ( std::string command; (std::getline(std::cin,command)); )
        {
            if ((command == "exit") || (command == "quit")) {
                break;
            }
            
            // ...
        }
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
