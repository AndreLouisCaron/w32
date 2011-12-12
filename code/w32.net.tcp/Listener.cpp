// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net.tcp/Listener.hpp>
#include <w32/Error.hpp>

namespace {

    ::SOCKET allocate ()
    {
#if 0
        const ::SOCKET result = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
        const ::DWORD flags = WSA_FLAG_OVERLAPPED;
        const ::SOCKET result = ::WSASocketW
            (AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, flags);
#endif
        if ( result == INVALID_SOCKET )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(socket, error);
        }
        return (result);
    }

}

namespace w32 { namespace net { namespace tcp {

    Listener::Listener ( const Socket::Handle& handle )
        : Socket(handle)
    {
    }

    Listener::Listener ( const ipv4::EndPoint& name, int backlog )
        : Socket(claim(::allocate()))
    {
        const ::sockaddr_in& address = name.data();
        const int result = ::bind(
            handle(), (::sockaddr*)&address, sizeof(address)
            );
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(bind, error);
        }
        if ( ::listen(handle(), backlog) == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(listen, error);
        }
    }

} } }
