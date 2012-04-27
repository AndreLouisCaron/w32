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

#include "__configure__.hpp"
#include "Handler.hpp"
#include "Service.hpp"

#include <iostream>

namespace {

    std::ostream& usage (std::ostream& stream)
    {
        return (stream
            << std::endl
            <<   "  Usage: ident-server                                     \n"
            <<   "         ident-server --help                              \n"
            <<   "                                                          \n"
            <<   "  Runs an ident[1] service, accepting network connections \n"
            <<   "  on port 113.  Remote computers may query this service   \n"
            <<   "  for the a unique identifier of the user running the     \n"
            <<   "  process with which the remote user is connected.        \n"
            <<   "                                                          \n"
            <<   "  Press CTRL+C or CTRL+BREAK to shutdown the service.     \n"
            <<   "                                                          \n"
            <<   "  [1]: http://tools.ietf.org/html/rfc1413                 \n"
            << std::endl);
    }

    // Shutdown with style, don't die abruptly.
    volatile bool running = true;
    io::CompletionPort *volatile completion_port = 0;
    ::BOOL __stdcall handle_console_event ( w32::dword event )
    {
        if ((event == CTRL_C_EVENT)||
            (event == CTRL_BREAK_EVENT)||
            (event == CTRL_CLOSE_EVENT))
        {
            // let the main loop know we're shutting down.
            running = false;

            // Make sure the main loop is not indefinitely blocked.
            if (completion_port) {
                completion_port->unblock_consumers();
            }

            return (TRUE);
        }

        // Let the default handler process all other events.
        return (FALSE);
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        const w32::ConsoleEventHandler _(&::handle_console_event);

        // Respond to usage request.
        if ((argc >= 2) && (::wcscmp(argv[1],L"--help")==0)) {
            std::cout
                << usage
                << std::endl;
            return (EXIT_SUCCESS);
        }

        // Intiialize network I/O services.
        net::Context network_context;
        io::CompletionPort completion_port;
        ::completion_port = &completion_port;

        // Listen for connections on standard port.
        tcp::Listener listener
            (ipv4::EndPoint(ipv4::Address::any(), 113));
        idp::Service service(completion_port, listener);

        // Process I/O completion notifications until we're told to stop.
        const w32::Timespan timeout =
            w32::Timespan(1, w32::Timespan::Unit::second());
        ::running = true;
        do {
            // Await and process the next completion notification.
            io::Notification notification = completion_port.next(timeout);
            if (idp::Handler* handler = notification.handler<idp::Handler>()) {
                handler->process(notification);
            }
            // On timeout, control handlers for timeouts.
            if (notification.timeout()) {
                service.control();
            }
        }
        while (::running);

        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
