// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/integers.hpp>
#include <w32/net/Context.hpp>
#include <w32/net/streambuf.hpp>
#include <w32/net/ipv4/Address.hpp>
#include <w32/net/ipv4/EndPoint.hpp>
#include <w32/net/udp/Socket.hpp>
#include <w32/diagnostics/UncheckedError.hpp>
#include <w32/diagnostics/StructuredException.hpp>
#include <iostream>
#include <string>

int main ( int arc, char ** argv )
{
    try
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
    }
    catch ( const w32::diagnostics::UncheckedError& error ) {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }
    catch ( const w32::diagnostics::StructuredException& error ) {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }
    catch ( const std::exception& error ) {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }
    catch ( ... ) {
        std::cerr << "Unknown failure." << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
