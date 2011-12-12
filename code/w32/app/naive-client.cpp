// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

    // This program should not link if compiled on standalone.
#include <w32/app/naive-client.hpp>

#include <w32.net.hpp>
#include <w32.hpp>
#include <iostream>
#include <string>

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        // Lock Windows Sockets library.
    const w32::net::Context _;
        
            // Setup connection parameters.
        const w32::net::Host host(w32::computername());
        const w32::net::ipv4::Address address =
            w32::net::ipv4::Address::local();
        const w32::net::uint16 port(4321);
        const w32::net::ipv4::EndPoint peer(address,port);
        
            // Connect to the server.
        w32::net::tcp::Stream stream(peer);
        
            // Use some convenient way to communicate.
        w32::net::sockstream channel(stream);
        
            // Let the client code work things from here!
        return (transaction(argc-2,argv+2,channel));
    }

}

#include <w32/app/console-program.cpp>
