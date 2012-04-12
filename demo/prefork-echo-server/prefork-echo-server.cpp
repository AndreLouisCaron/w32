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

#include <w32/app/prefork-server.hpp>

namespace {

    class Server
    {
        /* construction. */
    public:
        Server ( int argc, wchar_t ** argv )
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
