// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

    // Include this to get a linking error if compiled by itself.
#include <w32/net/tcp/naive-server.hpp>

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
        w32::net::tcp::Stream stream(listener);
        
            // Use some convenient way to communicate.
        w32::net::sockstream channel(stream);
        
            // Let the client code work things from here!
        return (transaction(channel));
    }

}

#include <w32/console-program.cpp>
