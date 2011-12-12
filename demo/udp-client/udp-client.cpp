// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net.hpp>

#include <iostream>
#include <string>

#include <w32/app/console-program.hpp>

namespace {

    int run ( int arc, wchar_t ** argv )
    {
        // Must load winsock2.
        w32::net::Context context;

        // Setup connection parameters.
        w32::net::ipv4::Address loopback("127.0.0.1");
        w32::net::uint16 port(1234);
        w32::net::ipv4::EndPoint host(loopback,port);
        w32::net::ipv4::EndPoint peer(loopback,port);

        w32::net::udp::Socket socket(host);

        const char buffer[] = "hello, world!";
        socket.put(peer,buffer,sizeof(buffer));

        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.net.lib" )
#pragma comment ( lib, "w32.net.ipv4.lib" )
#pragma comment ( lib, "w32.net.udp.lib" )
