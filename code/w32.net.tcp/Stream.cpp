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
 * @file w32.net.tcp/Stream.cpp
 * @author Andre Caron
 */

#include <w32.net.tcp/Stream.hpp>
#include <w32/Error.hpp>
#include <w32.io/InputStream.hpp>
#include <w32.io/OutputStream.hpp>

namespace {

        // Creates a socket for connection attempt.
    ::SOCKET allocate ()
    {
        const ::SOCKET result = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if ( result == INVALID_SOCKET ) {
            UNCHECKED_WIN32C_ERROR(socket,::WSAGetLastError());
        }
        return (result);
    }

        // Waits for a connection attempt from a client.
    ::SOCKET allocate ( ::SOCKET listener, ::sockaddr * peer, int * len )
    {
        const ::SOCKET result = ::accept(listener, peer, len);
        if ( result == INVALID_SOCKET ) {
            UNCHECKED_WIN32C_ERROR(accept,::WSAGetLastError());
        }
        return (result);
    }

    ::SOCKET allocate ( ::SOCKET listener, ::sockaddr_in& peer )
    {
        peer.sin_family = AF_INET; int len = sizeof(peer);
        const ::SOCKET result = ::accept(
            listener, reinterpret_cast<::sockaddr*>(&peer), &len);
        if ( result == INVALID_SOCKET ) {
            UNCHECKED_WIN32C_ERROR(accept,::WSAGetLastError());
        }
        return (result);
    }

    ::SOCKET allocate ( ::SOCKET listener )
    {
        const ::SOCKET result = ::accept(listener, 0, 0);
        if ( result == INVALID_SOCKET ) {
            UNCHECKED_WIN32C_ERROR(accept,::WSAGetLastError());
        }
        return (result);
    }

    ::HANDLE cast ( ::SOCKET handle )
    {
        return (reinterpret_cast< ::HANDLE >(handle));
    }

}

namespace w32 { namespace net { namespace tcp {

    Stream::Stream ( Handle handle )
        : StreamSocket(handle)
    {
    }

    Stream::Stream ( Listener& listener )
        : StreamSocket(claim( ::allocate(listener.handle()) ))
    {
    }

    Stream::Stream ( Listener& listener, ipv4::EndPoint& peer )
        : StreamSocket(claim(
            ::allocate(listener.handle(), peer.data())
            ))
    {
    }

    Stream::Stream ( const ipv4::EndPoint& peer )
        : StreamSocket(claim( ::allocate() ))
    {
        const ::sockaddr_in& address = peer.data();
        const int result = ::connect(
            handle(), (::sockaddr*)&address, sizeof(address)
            );
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error == WSAECONNREFUSED )
            {
            }
            UNCHECKED_WIN32C_ERROR(connect, error);
        }
    }

    ipv4::EndPoint Stream::host () const
    {
        ipv4::EndPoint endpoint;
        int size = sizeof(endpoint.data());
        const int result = ::getsockname(handle(), endpoint.raw(), &size);
        if (result == SOCKET_ERROR) {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(getsockname, error);
        }
        return (endpoint);
    }

    ipv4::EndPoint Stream::peer () const
    {
        ipv4::EndPoint endpoint;
        int size = sizeof(endpoint.data());
        const int result = ::getpeername(handle(), endpoint.raw(), &size);
        if (result == SOCKET_ERROR) {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(getpeername, error);
        }
        return (endpoint);
    }

    Stream::operator io::Stream () const
    {
        return (io::Stream(Object::proxy(::cast(handle()))));
    }

    Stream::operator io::InputStream () const
    {
        return (io::InputStream(Object::proxy(::cast(handle()))));
    }

    Stream::operator io::OutputStream () const
    {
        return (io::OutputStream(Object::proxy(::cast(handle()))));
    }

} } }
