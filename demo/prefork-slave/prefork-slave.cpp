// Copyright(c) 2009-2011 Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.net.hpp>

#include <iostream>
#include <sstream>

namespace {

    w32::net::tcp::Listener listener ( const wchar_t * argument )
    {
        ::SOCKET handle = INVALID_SOCKET;
        std::wistringstream parser(argument);
        if ( !(parser >> handle) ) {
            throw (std::exception("Could not parser listening socket handle."));
        }
        return (w32::net::tcp::Listener(w32::net::Socket::proxy(handle)));
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
          // prepare sockets library.
        const w32::net::Context _;
        
          // inherit listening socket handle from master process.
        if ( argc < 2 ) {
            throw (std::exception("Missing argument!"));
        }
        w32::net::tcp::Listener listener = ::listener(argv[1]);
        
        char data[16*1024];
        
            // accept connections from gateway.
        do {
            w32::net::tcp::Stream stream(listener);
            
            std::cout
                << "Accepted connection."
                << std::endl;
            
              // process data on transport connection.
            for ( w32::dword size; (size = stream.get(data,sizeof(data))) > 0; )
            {
                std::cout
                    << "Received '" << size << "' bytes."
                    << std::endl;
                for ( w32::dword used = 0; (used < size); ) {
                    used += stream.put(data+used, size-used);
                }
            }
            
            std::cout
                << "Client disconnected."
                << std::endl;
        }
        while ( false );
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>

#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.io.lib" )
#pragma comment ( lib, "w32.net.lib" )
#pragma comment ( lib, "w32.net.ipv4.lib" )
#pragma comment ( lib, "w32.net.tcp.lib" )
