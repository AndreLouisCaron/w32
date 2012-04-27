#ifndef _idp_AcceptRequest_hpp__
#define _idp_AcceptRequest_hpp__

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
 * @file demo/ident/AcceptRequest.hpp
 */

#include "__configure__.hpp"
#include "Buffer.hpp"

namespace idp {

    class AcceptRequest
    {
        /* data. */
    private:
        net::Socket::Handle myStream;
        io::Transfer myTransfer;

        Buffer * myBuffer;

        /* construction. */
    public:
        AcceptRequest ();

        /* methods. */
    public:
        // Start asynchronous accept operation.  Whenever a client connects,
        // the callback registered with the appropriate service will be
        // triggered.  That callback will process any data received with the
        // connection request.
        bool start ( tcp::Listener& listener );

        void cancel ( tcp::Listener& listener );

        void update_context ( tcp::Listener& listener );

        void recover_endpoints ( ipv4::EndPoint& host,
                                 ipv4::EndPoint& peer );

        void reset ();

        // Access the buffer containing data received with the connection.
        // The completion notification contains the number of bytes in this
        // buffer actually correspond to data sent by the peer.
        Buffer * buffer ();

        // Access the socket.  Only connected once the callback is triggered.
        tcp::Stream stream () const;

        bool started ( const io::Transfer& transfer ) const;
        bool started ( const ::OVERLAPPED& transfer ) const;
    };

}

#endif /* _idp_AcceptRequest_hpp__ */
