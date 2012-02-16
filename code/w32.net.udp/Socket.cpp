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
 * @file w32.net.udp/Socket.cpp
 * @author Andre Caron
 */

#include <w32.net.udp/Socket.hpp>
#include <w32/Error.hpp>

namespace {

    ::SOCKET allocate ()
    {
        const ::SOCKET result = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        if ( result == INVALID_SOCKET ) {
            UNCHECKED_WIN32C_ERROR(socket,::WSAGetLastError());
        }
        return (result);
    }

}

namespace w32 { namespace net { namespace udp {

    Socket::Socket ( const ipv4::EndPoint& name )
        : DatagramSocket(::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))
    {
    }

    int Socket::get ( ipv4::EndPoint& peer, void * buffer, int bytes )
    {
        ::sockaddr_in& address = peer.data();
        return (get(&address,sizeof(address),buffer,bytes));
    }

    int Socket::put (
        const ipv4::EndPoint& peer, const void * buffer, int bytes )
    {
        const ::sockaddr_in& address = peer.data();
        return (put(&address,sizeof(address),buffer,bytes));
    }

} } }
