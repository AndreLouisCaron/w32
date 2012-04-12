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
        w32::net::ipv4::EndPoint peer(w32::net::ipv4::Address::any(), port);
        
            // Wait for a client connection.
        w32::net::udp::Socket socket(host);
        
        char buffer[1024] = { 0 };
        socket.get(peer,buffer,sizeof(buffer));
        
        std::cout << buffer << std::endl;

        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
