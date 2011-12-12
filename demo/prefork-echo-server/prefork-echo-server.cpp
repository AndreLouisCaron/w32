// Copyright(c) 2009-2011 Andre Caron (andre.l.caron@gmail.com)
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.net.hpp>

#include <w32/app/prefork-server.hpp>

namespace {

    class Server
    {
        /* construction. */
    public:
        Server ()
        {
        }

        /* operators. */
    public:
        bool operator() ( w32::net::tcp::Stream& stream )
        {
              // allocate buffer for this connection.
            char data[16*1024];
            
              // echo data sent by peer until peer is fed up and quits.
            for ( w32::dword size; (size=stream.get(data,sizeof(data))) > 0; )
            {
                std::cout
                    << "Received '" << size << "' bytes."
                    << std::endl;
                for ( w32::dword used = 0; (used < size); ) {
                    used += stream.put(data+used, size-used);
                }
            }
            
              // allow accepting infinite connections.
            return (true);
        }
    };

}

#include <w32/app/prefork-server.cpp>

#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.io.lib" )
#pragma comment ( lib, "w32.net.lib" )
#pragma comment ( lib, "w32.net.ipv4.lib" )
#pragma comment ( lib, "w32.net.tcp.lib" )
