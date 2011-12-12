// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net/tcp/threaded-server.hpp>

#include <w32.hpp>
#include <w32.mt.hpp>
#include <w32.net.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace {

    w32::dword thread ( void * parameter )
    {
        const std::auto_ptr<w32::net::tcp::Stream> argument
            (reinterpret_cast<w32::net::tcp::Stream*>(parameter));
        w32::net::sockstream channel(*argument);
        return (transaction(channel));
    }

    w32::mt::Thread::Function callback ()
    {
        return (w32::mt::Thread::adapt
            <w32::dword, void*, &thread>());
    }

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // Must load Windows Sockets environment.
        w32::net::Context context;
        
            // Setup connection parameters.
        w32::net::Host host(w32::computername());
        w32::net::ipv4::Address address
            (host.address<w32::net::ipv4::Address>(0));
        w32::net::uint16 port(4321);
        w32::net::ipv4::EndPoint endpoint(address,port);
        
            // Wait for a client connection.
        w32::net::tcp::Listener listener(endpoint);
        while ( true )
        {
                // Launch a thread to handle the client.
            w32::mt::Thread
                (callback(), new w32::net::tcp::Stream(listener));
        }
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>
