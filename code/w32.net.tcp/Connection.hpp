#ifndef _w32_net_tcp_Connection_hpp__
#define _w32_net_tcp_Connection_hpp__

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
 * @file w32.net.tcp/Connection.hpp
 */

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace net { namespace ipv4 {

    class Address;
    class EndPoint;

} } }

namespace w32 { namespace net { namespace tcp {

    class State;

    //! @addtogroup w32-net
    //! @{

    class Connection
    {
        /* nested types. */
    public:
        typedef ::MIB_TCPROW2 Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Connection ( const Data& data );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        State state () const;

        w32::uint16 host_port () const;
        w32::uint16 peer_port () const;

        ipv4::Address host_name () const;
        ipv4::Address peer_name () const;

        ipv4::EndPoint host () const;
        ipv4::EndPoint peer () const;

        w32::dword process () const;
    };

    //! @}

} } }

#endif /* _w32_net_tcp_Connection_hpp__ */
