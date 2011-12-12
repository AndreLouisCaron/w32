// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net/DatagramSocket.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace net {

    DatagramSocket::DatagramSocket ( Handle handle )
        : Socket(handle)
    {
    }

    int DatagramSocket::put (
        const void * peer, int size, const void * buffer, int length
        )
    {
        const int result = ::sendto(
            handle(), static_cast<const char*>(buffer), length,
            0, static_cast<const ::sockaddr*>(peer), size
            );
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(shutdown, error);
        }
        return (result);
    }

    int DatagramSocket::get ( void * peer, int size, void * buffer, int length )
    {
        const int result = ::recvfrom(
            handle(), static_cast<char*>(buffer), length,
            0, static_cast<::sockaddr*>(peer), &size
            );
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(shutdown, error);
        }
        return (result);
    }

} }
