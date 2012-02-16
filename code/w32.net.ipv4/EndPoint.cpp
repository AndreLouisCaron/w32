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
 * @file w32.net.ipv4/EndPoint.cpp
 * @author Andre Caron
 */

#include <w32.net.ipv4/EndPoint.hpp>
#include <w32/Error.hpp>
#include <w32.net./StreamSocket.hpp>
#include <iostream>

namespace w32 { namespace net { namespace ipv4 {

    EndPoint::EndPoint ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.sin_family = AF_INET;
    }

    EndPoint::EndPoint ( const Data& data )
    {
        ::CopyMemory(&myData, &data, sizeof(myData));
    }

    EndPoint::EndPoint ( uint32 address, uint16 port )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.sin_family = AF_INET;
        myData.sin_addr.S_un.S_addr = address.raw();
        myData.sin_port = port.raw();
    }

    EndPoint::EndPoint ( uint8 b1, uint8 b2, uint8 b3, uint8 b4, uint16 port )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.sin_family = AF_INET;
        myData.sin_addr.S_un.S_un_b.s_b1 = b1;
        myData.sin_addr.S_un.S_un_b.s_b2 = b2;
        myData.sin_addr.S_un.S_un_b.s_b3 = b3;
        myData.sin_addr.S_un.S_un_b.s_b4 = b4;
        myData.sin_port = port.raw();
    }

    EndPoint::EndPoint ( const Address& address, uint16 port )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.sin_family = AF_INET;
        myData.sin_addr.S_un.S_addr = address.value().S_un.S_addr;
        myData.sin_port = port.raw();
    }

    EndPoint::EndPoint ( const EndPoint& other )
    {
        ::CopyMemory(&myData, &other.myData, sizeof(myData));
    }

    EndPoint::Data& EndPoint::data ()
    {
        return (myData);
    }

    const EndPoint::Data& EndPoint::data () const
    {
        return (myData);
    }

    ::sockaddr * EndPoint::raw ()
    {
        return (reinterpret_cast<::sockaddr*>(&myData));
    }

    const ::sockaddr * EndPoint::raw () const
    {
        return (reinterpret_cast<const ::sockaddr*>(&myData));
    }

    int EndPoint::size () const
    {
        return (sizeof(myData));
    }

    uint16 EndPoint::port () const
    {
        return (uint16(uint16::box(myData.sin_port)));
    }

    Address EndPoint::address () const
    {
        return (Address(
            myData.sin_addr.S_un.S_un_b.s_b1,
            myData.sin_addr.S_un.S_un_b.s_b2,
            myData.sin_addr.S_un.S_un_b.s_b3,
            myData.sin_addr.S_un.S_un_b.s_b4));
    }

    EndPoint& EndPoint::operator= ( const Data& data )
    {
        ::CopyMemory(&myData, &data, sizeof(myData));
        return (*this);
    }

    EndPoint host ( const StreamSocket& socket )
    {
        const ::SOCKET handle = socket.handle();

        ::sockaddr_in endpoint;
        ::ZeroMemory(&endpoint, sizeof(endpoint));
        endpoint.sin_family = AF_INET;

        int size = sizeof(endpoint);
        const int result = ::getsockname
            (handle, reinterpret_cast<::sockaddr*>(&endpoint), &size);
        if (result == SOCKET_ERROR)
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(getsockname, error);
        }
        return (EndPoint(endpoint));
    }

    EndPoint peer ( const StreamSocket& socket )
    {
        const ::SOCKET handle = socket.handle();

        ::sockaddr_in endpoint;
        ::ZeroMemory(&endpoint, sizeof(endpoint));
        endpoint.sin_family = AF_INET;

        int size = sizeof(endpoint);
        const int result = ::getpeername
            (handle, reinterpret_cast<::sockaddr*>(&endpoint), &size);
        if (result == SOCKET_ERROR)
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(getsockname, error);
        }
        return (EndPoint(endpoint));
    }

    std::istream& operator>> ( std::istream& stream, EndPoint& value )
    {
          // parse the host.
        Address host;
        if ( !(stream >> host) ) {
            stream.setstate(std::ios::failbit); return (stream);
        }
          // parse the port.
        if ( stream.peek() != ':' ) {
            stream.setstate(std::ios::failbit); return (stream);
        }
        stream.ignore();
        int port = -1;
        if ( !(stream >> port) || (port < 0) || (port >= (1<<15)) ) {
            stream.setstate(std::ios::failbit); return (stream);
        }
          // build end pair.
        value = w32::net::ipv4::EndPoint(host, port);
        return (stream);
    }

    std::ostream& operator<< ( std::ostream& out, const EndPoint& value )
    {
        return (out
            << (int)value.data().sin_addr.S_un.S_un_b.s_b1 << '.'
            << (int)value.data().sin_addr.S_un.S_un_b.s_b2 << '.'
            << (int)value.data().sin_addr.S_un.S_un_b.s_b3 << '.'
            << (int)value.data().sin_addr.S_un.S_un_b.s_b4 << ':'
            << (int)::ntohs(value.data().sin_port));
    }

} } }
