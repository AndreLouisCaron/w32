#ifndef _idp_Session_hpp__
#define _idp_Session_hpp__

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
#include "idp_iwire.h"

#include <ctime>

namespace idp {

    class Buffer;

    class Session :
        public Handler
    {
        /* class methods. */
    private:
        static int query (::idp_iwire * stream);

        /* data. */
    private:
        Service& myService;
        tcp::Stream myStream;
        Buffer * myGBuffer;
        Buffer * myPBuffer;
        ipv4::EndPoint myHost;
        ipv4::EndPoint myPeer;

        io::Transfer myGet;
        io::Transfer myPut;

        ::idp_iwire myWire;

        std::clock_t myLastGet; // 0-> not pending.
        std::clock_t myLastPut; // 0-> not pending.

        /* construction. */
    public:
        Session (Service& service, tcp::Stream stream, Buffer * buffer,
                 ipv4::EndPoint host, ipv4::EndPoint peer);
        virtual ~Session ();

        /* methods. */
    private:
        /*!
         * @brief Perform the ident service lookup.
         * @param server_port
         * @param client_port
         * @return @c true if there is enough buffer space to accept another
         *  query right away, @c false if the response should be sent right
         *  away.
         *
         * Lookup in the TCP connections table is also limited by the peer IP
         * retrieved when establishing the connection.  This is for security
         * purposes: it ensures that a third party cannot use this service to
         * obtain information about connections with other peers.
         */
        bool lookup (int server_port, int client_port);

        /* overrides. */
    public:
        virtual bool control ();
        virtual void process (const io::Notification& notification);
    };

}

#endif /* _idp_Session_hpp__ */
