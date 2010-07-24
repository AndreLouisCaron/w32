// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/tcp/Stream.hpp>
#include <w32/Error.hpp>

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
    ::SOCKET allocate ( ::SOCKET listener )
    {
        const ::SOCKET result = ::accept(listener,0,0);
        if ( result == INVALID_SOCKET ) {
            UNCHECKED_WIN32C_ERROR(accept,::WSAGetLastError());
        }
        return (result);
    }

}

namespace w32 { namespace net { namespace tcp {

    Stream::Stream ( Listener& listener )
        : StreamSocket(claim( ::allocate(listener.handle()) ))
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

} } }
