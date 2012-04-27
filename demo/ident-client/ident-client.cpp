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

/*!
 * @file demo/ident-client/ident-client.cpp
 */

#include <w32.net.hpp>
#include <w32.hpp>

namespace net  = w32::net;
namespace ipv4 = w32::net::ipv4;
namespace tcp  = w32::net::tcp;

#include <iostream>
#include <string>
#include <sstream>

namespace {

    std::ostream& usage (std::ostream& stream)
    {
        return (stream
            << std::endl
            <<   "  Usage: ident-client host client-port server-port        \n"
            <<   "         ident-client --help                              \n"
            <<   "                                                          \n"
            <<   "  Arguments:                                              \n"
            <<   "    host       : server IP address.                       \n"
            <<   "    client-port: integer in [0,65536).                    \n"
            <<   "    server-port: integer in [0,65536).                    \n"
            <<   "                                                          \n"
            <<   "  Queries an ident[1] service for the remote user name    \n"
            <<   "  of the entity running a network-bound process on the    \n"
            <<   "  remote computer.  The process is identified by a pair   \n"
            <<   "  of local and remote ports.  In the query, the client    \n"
            <<   "  is the machine running this command and the server is   \n"
            <<   "  the machine running the ident service.                  \n"
            <<   "                                                          \n"
            <<   "  [1]: http://tools.ietf.org/html/rfc1413                 \n"
            << std::endl);
    }

}

#include <w32/app/console-program.hpp>

namespace {

    void put (tcp::Stream& stream, const std::string& payload)
    {
        // Try to send the entire payload.
        int used = 0;
        int pass = 0;
        do {
            pass = stream.put(payload.data()+used, payload.size()-used);
        }
        while ((pass > 0) && ((used += pass) < payload.size()));

        // Make sure all the data was sent.
        if (used < payload.size()) {
            std::cerr << "Connection closed?" << std::endl;
        }
    }

    int run ( int argc, wchar_t ** argv )
    {
        // Respond to usage request.
        if ((argc >= 2) && (::wcscmp(argv[1],L"--help")==0)) {
            std::cout
                << usage
                << std::endl;
            return (EXIT_SUCCESS);
        }

        // Parse command-line arguments.
        int server_port = 113;
        int client_port = 0;

        // Intiialize an I/O service.
        net::Context network_context;

        // Listen for connections on standard port.
        ipv4::Address host = ipv4::Address::local();
        tcp::Stream stream(ipv4::EndPoint(host, 113));

        client_port = stream.host().port();
        std::cout
            << "client-port: " << client_port
            << std::endl
            ;

        std::ostringstream query;
        query
            << server_port << ", " << client_port
            << std::endl
            ;
        put(stream, query.str());

        char data[512];
        int size = 512;
        int pass = 0;
        int used = 0;
        do {
            pass = stream.get(data+used, size-used);
        }
        while ((pass > 0) && ((used += pass) < size));

        std::cout.write(data, used) << " (" << used << ")" << std::endl;

        // Don't send multiple queries.
        stream.shutdown();

        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
