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
#include <w32.ipc.hpp>
#include <w32.net.hpp>

#include <iostream>
#include <sstream>
#include <vector>

namespace {

    w32::string slave_command
        ( const w32::string& path, w32::net::Socket::Handle handle )
    {
        std::wostringstream command;
        command
            << '"' << path << '"' << " " << handle;
        return (command.str().c_str());
    }

    w32::net::ipv4::EndPoint listener ( const w32::astring& argument )
    {
        std::istringstream stream(argument.c_str());
        w32::net::ipv4::EndPoint endpoint;
        if ( !(stream >> endpoint) ) {
            throw (std::invalid_argument("endpoint"));
        }
        return (endpoint);
    }

    w32::net::ipv4::EndPoint listener ( const w32::string& endpoint )
    {
        return (listener(w32::astring(endpoint, w32::Codepage::ansi())));
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
          // prepare sockets library.
        const w32::net::Context _;
        
          // configure master process.
        w32::net::ipv4::EndPoint endpoint
            (w32::net::ipv4::Address::any(), 8000);
        if ( argc > 1 ) {
            endpoint = ::listener(w32::string(argv[1]));
        }
        const w32::dword slavecount = 1;
        const w32::string slavepath = L"../../.build/dbg/prefork-slave.exe";
        
        std::wcout
            << L"Online in: '" << w32::currentdirectory() << "'"
            << std::endl;
        
        std::cout
            << "Opening listening socket, binding to '" << endpoint << "'."
            << std::endl;
        
          // start listening for connections.
        w32::net::tcp::Listener listener(endpoint);
        
        std::cout
            << "Starting slaves."
            << std::endl;
        
          // create slave processes.
        const w32::string slavecommand =
            ::slave_command(slavepath, listener.handle());
        std::vector<w32::ipc::Process> slaves;
        slaves.reserve(slavecount);
        w32::Waitable::Set objects;
        for ( w32::dword i = 0; (i < slavecount); ++i ) {
            const w32::ipc::Process slave(slavecommand, true);
            slaves.push_back(slave), objects |= slave.handle();
        }
        
        std::cout
            << "Monitoring slaves."
            << std::endl;
        
        bool running = false;
        
          // monitor slave processes and re-spawn when necessary.
        do {
              // wait for any slave process to complete.
            const w32::dword i = w32::Waitable::any(objects);
              // check slave process status, log errors.
            const w32::dword status = slaves[i].status();
            if ( status == 0 )
            {
                std::cout
                    << "Slave process finished."
                    << std::endl;
            }
            else
            {
                std::cerr
                    << "Slave process crashed (" << status << ")."
                    << std::endl;
            }
            
              // replace slave process with fresh instance.
            objects &= slaves[i].handle();
            if ( running ) {
                slaves[i] = w32::ipc::Process(slavecommand, true);
                objects |= slaves[i].handle();
            }
        }
        while ( running );
        
        std::cout
            << "Waiting for slaves."
            << std::endl;
        if ( !objects.empty() ) {
            w32::Waitable::all(objects);
        }
        std::cout
            << "Over and out."
            << std::endl;
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
