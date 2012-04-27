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

#include "Service.hpp"
#include "Session.hpp"

namespace idp {

    Service::Service
        (io::CompletionPort& completion_port, tcp::Listener listener)
        : myCompletionPort(completion_port)
        , myListener(listener)
    {
        // Register for asynchronous I/O completion notifications.
        myCompletionPort
            .bind(myListener.handle(), static_cast<Handler*>(this));

        // Start listening for incoming connections.
        if (!myRequest.start(myListener)) {
            // ...
        }
    }

    io::CompletionPort& Service::completion_port ()
    {
        return (myCompletionPort);
    }

    bool Service::control ()
    {
        typedef std::set<Session*>::iterator iterator;
        iterator current = mySessions.begin();
        const iterator end = mySessions.end();
        while (current != end) {
            Session *const session = *current;
            if (session->control()) {
                current = mySessions.erase(current); delete session;
            }
            else {
                ++current;
            }
        }
        return (false);
    }

    void Service::process (const io::Notification& notification)
    try
    {
        if (!notification.timeout() && !notification.aborted()) {
            notification.report_error();
        }

        // Handle incoming connection.
        if (notification.transfer() &&
            myRequest.started(*notification.transfer()))
        {
            // Update the buffer, some data is already available.
            myRequest.buffer()->gave(notification.size());

            // Inherit the listening socket's properties.
            myRequest.update_context(myListener);

            // Fetch connection end points.
            ipv4::EndPoint host;
            ipv4::EndPoint peer;
            myRequest.recover_endpoints(host, peer);

            // Register the new connection.
            mySessions.insert(new Session(*this, myRequest.stream(),
                                          myRequest.buffer(), host, peer));

            // Start another connection request.
            myRequest.reset();
            if (!myRequest.start(myListener)) {
                // failed ...
            }
        }
    }
    catch (const w32::Error& error)
    {
        // ...
    }

}
