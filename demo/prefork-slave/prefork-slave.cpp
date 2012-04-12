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
