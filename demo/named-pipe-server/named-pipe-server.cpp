// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.io.hpp>

namespace {

    const wchar_t PIPE_NAME[] =
        L"\\\\.\\pipe\\w32++.demo.named-pipe";

}

#include <w32/console-program.hpp>

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

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.io.lib" )
