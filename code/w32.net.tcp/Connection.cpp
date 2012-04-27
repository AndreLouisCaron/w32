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
 * @file w32.net.tcp/Connection.cpp
 */

#include "Connection.hpp"
#include "State.hpp"
#include <w32.net.ipv4/Address.hpp>
#include <w32.net.ipv4/EndPoint.hpp>

namespace w32 { namespace net { namespace tcp {

    Connection::Connection ( const Data& data )
        : myData(data)
    {
    }

    Connection::Data& Connection::data ()
    {
        return (myData);
    }

    const Connection::Data& Connection::data () const
    {
        return (myData);
    }

    State Connection::state () const
    {
        return (State::of(*this));
    }

    w32::uint16 Connection::host_port () const
    {
        return (::ntohs(static_cast<w32::uint16>(myData.dwLocalPort)));
    }

    w32::uint16 Connection::peer_port () const
    {
        return (::ntohs(static_cast<w32::uint16>(myData.dwRemotePort)));
    }

    ipv4::Address Connection::host_name () const
    {
        return (ipv4::Address(myData.dwLocalAddr));
    }

    ipv4::Address Connection::peer_name () const
    {
        return (ipv4::Address(myData.dwRemoteAddr));
    }

    ipv4::EndPoint Connection::host () const
    {
        return (ipv4::EndPoint(host_name(), host_port()));
    }

    ipv4::EndPoint Connection::peer () const
    {
        return (ipv4::EndPoint(peer_name(), peer_port()));
    }

    w32::dword Connection::process () const
    {
        return (myData.dwOwningPid);
    }

} } }
