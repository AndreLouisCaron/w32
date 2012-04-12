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
#include <w32.io.hpp>

namespace {

    const wchar_t PIPE_NAME[] =
        L"\\\\.\\pipe\\w32++.demo.named-pipe";

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        std::cout << "Acquiring pipe." << std::endl;
        
          // Create pipe.
        w32::io::NamedPipe pipe =
            w32::io::NamedPipe::create(::PIPE_NAME, 1024);
        
        std::cout << "Waiting for connection." << std::endl;
        
          // Wait for client to connect.
        pipe.connect();
        
        std::cout << "Sending message." << std::endl;
        
          // Send the client a message.
        char message[] = "Hello, client!";
        pipe.put((w32::byte*)message, sizeof(message)-1);
        
        std::cout << "Waiting for response." << std::endl;
        
          // Wait for a reply.
        pipe.get((w32::byte*)message, sizeof(message)-1);
        
          //  Display peer's message.
        std::cout << message << std::endl;
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
