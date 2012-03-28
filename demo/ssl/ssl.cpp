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
 * @file demo/ssl/ssl.cpp
 * @brief Simple SSL demonstration.
 */

#include <w32.hpp>
#include <w32.cr.hpp>
#include <w32.mt.hpp>
#include <w32.net.hpp>

namespace {

    static const w32::net::ipv4::EndPoint endpoint(127,0,0,1,1234);

    w32::dword background ( void * )
    {
            // Get a communications channel.
        w32::net::tcp::Stream stream(endpoint);
        w32::cr::Channel channel(stream);
        
            // Perform hand-shake.
        channel.client(L"");
        
            // Wait for server to send something!
        w32::mt::sleep(w32::Timespan(500));
        
            // Read data sent over secure channel.
        char data[1024]; ::ZeroMemory(data, sizeof(data));
        channel.get(data, stream.get(data,1024));
        data[13] = '\0';
        std::cout << "  -- '" << data << "'." << std::endl;

        return (0);
    }

    inline w32::mt::Thread::Function callback ()
    {
        return (w32::mt::Thread::function<&background>());
    }

}

#include <w32/app/console-program.hpp>

namespace {

    /*!
     * @brief Get a cryptographic provider that operates on @a container.
     * @param container The name of the container to open.
     * @return A cryptographic provider.
     *
     * If the container does not already exists, the function creates it.
     */
    w32::cr::Provider get_provider ( const w32::string& container )
    {
        const w32::cr::Provider::Type type  =
            w32::cr::Provider::Type::rsafull();

        // Try creating the key in an existing container.
        w32::cr::Provider::Hints hints;
        hints
            .machineKeySet()
            ;
        try {
            return (w32::cr::Provider(type, hints, container));
        }
        catch (const w32::Error& error)
        {
            // If the container does not exist, create it.
            if (error.code() != NTE_BAD_KEYSET) {
                throw;
            }
            hints
                .newKeySet()
                ;
            return (w32::cr::Provider(type, hints, container));
        }
    }

    int run ( int argc, wchar_t ** argv )
    {
        w32::net::Context _;

        // Access the provider and create or update the container.
        w32::cr::Provider provider = get_provider(L"my-new-container");

        // Host a server locally in the current process.
        w32::net::tcp::Listener listener(endpoint);
        
        // Server identity.
        const w32::string subject =
            L"CN=Example,"
            L"O=Example Inc.,"
            L"E=admin@example.qc.ca,"
            L"C=Canada,"
            L"S=QC,"
            ;
        const w32::cr::Certificate certificate =
            w32::cr::Certificate::self_signed(provider, subject);
        
        // Launch the client-side code in background thread.
        w32::mt::Thread thread(::callback());
        
        // Wait for a pending connection from the client.
        while ( !w32::net::readable(listener) ) {
            w32::mt::sleep(w32::Timespan(5));
        }
        w32::net::tcp::Stream stream(listener);
        
        // Get a communications channel.
        w32::cr::Channel channel(stream);
        
        // Perform hand-shake.
        try {
            channel.server(certificate);
            channel.put("Hello, world!", 13);
        }
        catch ( const std::exception& error ) {
            std::cerr << "[[[ SERVER FAILED! ]]]" << std::endl;
            std::cout << error.what() << std::endl;
        }
        
        thread.join();
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
