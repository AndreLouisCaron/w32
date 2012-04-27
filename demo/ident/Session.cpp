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

#include "Session.hpp"
#include <iostream>
#include <sstream>

namespace {

    w32::string mangle ( const w32::string& username )
    {
        // Get a cryptographic context for user name mangling.
        w32::cr::Provider::Hints hints;
        hints
            .silent()
            .verifyContext();
        w32::cr::Provider provider
            (w32::cr::Provider::Type::rsafull(), hints);

        // Mangle the user name, for security.
        const w32::astring name(username, w32::Codepage::utf8());
        const w32::cr::Hash hash =
            w32::cr::sha1(provider, name.data(), name.size());
        return (w32::cr::convert(hash.data()));
    }

}

namespace idp {

    int Session::query (::idp_iwire * stream)
    {
        return (static_cast<Session*>(stream->baton)
                ->lookup(stream->server_port, stream->client_port)? 0 : 1);
    }

    Session::Session (Service& service, tcp::Stream stream, Buffer * buffer,
                      ipv4::EndPoint host, ipv4::EndPoint peer)
        : myService(service)
        , myStream(stream)
        , myGBuffer(buffer)
        , myPBuffer(new Buffer(512))
        , myHost(host)
        , myPeer(peer)
        , myLastGet(0)
        , myLastPut(0)
    {
        // Register for asynchronous I/O completion notifications.
        myService.completion_port()
            .bind(myStream, static_cast<Handler*>(this));

        // Initialize ident protocol query parser.
        ::idp_iwire_init(&myWire);
        myWire.baton = this;
        myWire.query = &Session::query;

        // Start another transfer.
        if (myStream.get(myGBuffer->next(), myGBuffer->left(), myGet))
        {
            // ...
        }
        myLastGet = std::clock();

        // Parse data received while connecting.
        myGBuffer->took(::idp_iwire_feed
                        (&myWire, myGBuffer->data(), myGBuffer->size()));
    }

    Session::~Session ()
    {
        std::cout << __FUNCSIG__ << std::endl;

        delete myGBuffer; myGBuffer = 0;
        delete myPBuffer; myPBuffer = 0;
    }

    bool Session::lookup (int server_port, int client_port)
    {
        bool match_found = false;

        // Lookup matching connection in TCP table.
        tcp::Connections connections;
        for (w32::dword i=0; !match_found && (i < connections.size()); ++i)
        {
            const tcp::Connection connection = connections[i];
            if ((connection.state() == tcp::State::established())
                && (connection.host_port() == server_port)
                && (connection.peer_port() == client_port)
                && (connection.peer_name() == myPeer.address()))
            {
                // Find the user account owning the process.
                w32::ipc::Process::Access access;
                access
                    .query_information()
                    ;
                w32::ipc::Process process(connection.process(), access);
                w32::sy::Token token = w32::sy::Token::of(process);
                w32::sy::User user(token);
                w32::sy::Account account(user);
                w32::string name = account.username();

                // Mangle the name and encode it to ASCII.
                if (false) {
                    name = mangle(name);
                }
                const w32::astring username(name);

                // Write the ident response.
                std::ostringstream response;
                response
                    << server_port << ", " << client_port
                    << " : USERID : OTHER : " << username
                    << std::endl
                    ;
                myPBuffer->put(response.str());

                match_found = true;
            }
        }

        if (!match_found)
        {
            // Write the ident response.
            std::ostringstream response;
            response
                << server_port << ", " << client_port
                << " : ERROR : UNKNOWN-ERROR"
                << std::endl
                ;
            myPBuffer->put(response.str());
        }

        // Send the response.
        if (myPBuffer->size() > 0)
        {
            if (myStream.put(myPBuffer->data(), myPBuffer->size(), myPut))
            {
                // ...
            }
            myLastPut = std::clock();
        }

        // Don't handle multiple responses in a single iteration.
        return (false);
    }

    bool Session::control ()
    {
        // If there are no pending in-bound or out-bound transfers,
        // we have already received a shutdown from the peer and we
        // have no data left to send, so just close the connection.
        if ((myLastGet == 0) && (myLastPut == 0)) {
            myStream.shutdown(); return (true);
        }

        // Apply timeouts for asynchronous I/O operations.
        const std::clock_t now = std::clock();
        if ((myLastGet != 0) && ((now-myLastGet)/CLOCKS_PER_SEC) > 5) {
            myStream.cancel(myGet);
        }
        if ((myLastPut != 0) && ((now-myLastPut)/CLOCKS_PER_SEC) > 5) {
            myStream.cancel(myPut);
        }

        // Not quite ready to die yet.
        return (false);
    }

    void Session::process (const io::Notification& notification)
    try
    {
        if (!notification.timeout() && !notification.aborted()) {
            notification.report_error();
        }

        io::Transfer *const xfer = notification.transfer();

        // Handle incoming data.
        if (xfer == &myGet)
        {
            // Transfer finished, clear transfer state.
            myLastGet = 0, myGet.clear();

            // Update valid buffer range.
            myGBuffer->gave(notification.size());

            // Consume input data.
            myGBuffer->took(::idp_iwire_feed
                            (&myWire, myGBuffer->data(), myGBuffer->size()));
            if (myWire.error != ::idp_iwire_good)
            {
                // Handle syntax error (close connection).
                // ...

                std::cout
                    << "Syntax error."
                    << std::endl;
                return;
            }

            // Start another transfer.
            if (notification.size() > 0)
            {
                if (myStream.get(myGBuffer->next(), myGBuffer->left(), myGet))
                {
                    // ...
                }
                myLastGet = std::clock();
            }
        }

        // Handle outgoing data.
        if (xfer == &myPut)
        {
            // Transfer finished, clear transfer state.
            myLastPut = 0, myPut.clear();

            // Update valid buffer range.
            myPBuffer->took(notification.size());
            myPBuffer->pack();

            // Start another transfer.
            if (notification.size() > 0)
            {
                if (myPBuffer->size() > 0) {
                    if (myStream.put(myPBuffer->data(),
                                     myPBuffer->size(), myPut))
                    {
                        // ...
                    }
                    myLastPut = std::clock();
                }
            }
        }
    }
    catch (const w32::Error& error)
    {
        // ...
    }

}
