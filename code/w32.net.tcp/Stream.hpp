#ifndef _w32_net_tcp_Stream_hpp__
#define _w32_net_tcp_Stream_hpp__

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
 * @file w32.net.tcp/Stream.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32.net/StreamSocket.hpp>
#include <w32.net.ipv4/EndPoint.hpp>
#include <w32.net.tcp/Listener.hpp>

namespace w32 { namespace io {

    class InputStream;
    class OutputStream;
    class Stream;

} }

namespace w32 { namespace net { namespace tcp {

    /*!
     * @ingroup w32-net
     * @brief Transfer Control Protocol, connection socket.
     */
    class Stream :
        public StreamSocket
    {
        /* nested types. */
    public:
        typedef ::LPFN_CONNECTEX ConnectEx;

        /* class methods. */
    public:
        static ConnectEx lookup_connect_ex (::SOCKET handle);

        /* construction. */
    public:
        /*!
         * @brief Wrap an existing TCP socket stream handle.
         */
        explicit Stream ( Handle handle );

            /*!
             * @brief Wait for a connection (server side).
             */
        Stream ( Listener& listener );
        Stream ( Listener& listener, ipv4::EndPoint& peer );

            /*!
             * @brief Connect to a server (client side).
             */
        Stream ( const ipv4::EndPoint& peer );

        /* methods. */
    public:
        ipv4::EndPoint host () const;
        ipv4::EndPoint peer () const;

        ConnectEx connect_ex () const;

        /* operators . */
    public:
        operator io::Stream () const;
        operator io::InputStream () const;
        operator io::OutputStream () const;
    };

} } }

#endif /* _w32_net_tcp_Stream_hpp__ */
