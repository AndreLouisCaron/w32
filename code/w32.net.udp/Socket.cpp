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
