// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net/StreamSocket.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace net {

    StreamSocket::StreamSocket ( const Handle& handle )
        : Socket(handle)
    {
    }

    StreamSocket::~StreamSocket ()
    {
    }

    int StreamSocket::put ( const void * buffer, int length )
    {
        const int result = ::send
            (handle(), static_cast<const char*>(buffer), length, 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(shutdown, error);
        }
        return (result);
    }

    int StreamSocket::get ( void * buffer, int length )
    {
        const int result = ::recv
            (handle(), static_cast<char*>(buffer), length, 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error == WSAECONNRESET ) {
                return (0);
            }
            if ( error == WSAEWOULDBLOCK ) {
                return (-1);
            }
            UNCHECKED_WIN32C_ERROR(recv, error);
        }
        return (result);
    }

    int StreamSocket::put ( Buffer& buffer )
    {
        ::DWORD bytes = 0; ::DWORD flags = 0;
        const int result = ::WSASend
            (handle(), &buffer.data(), 1, &bytes, flags, 0, 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(WSASend, error);
        }
        return (result);
    }

    int StreamSocket::get ( Buffer& buffer )
    {
        ::DWORD bytes = 0; ::DWORD flags = 0;
        const int result = ::WSARecv
            (handle(), &buffer.data(), 1, &bytes, &flags, 0, 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error == WSAECONNRESET ) {
                return (0);
            }
            UNCHECKED_WIN32C_ERROR(WSARecv, error);
        }
        return (result);
    }

    void StreamSocket::put ( Buffer& buffer, io::Transfer& transfer )
    {
        ::DWORD bytes = 0; ::DWORD flags = 0;
        const int result = ::WSASend
            (handle(), &buffer.data(), 1, &bytes, flags, &transfer.data(), 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error != WSA_IO_PENDING ) {
                UNCHECKED_WIN32C_ERROR(WSASend, error);
            }
            std::cerr << "StreamSocket: output request pending!" << std::endl;
        }
    }

    void StreamSocket::get ( Buffer& buffer, io::Transfer& transfer )
    {
        ::DWORD bytes = 0; ::DWORD flags = 0;
        const int result = ::WSARecv
            (handle(), &buffer.data(), 1, &bytes, &flags, &transfer.data(), 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error != WSA_IO_PENDING ) {
                UNCHECKED_WIN32C_ERROR(WSARecv, error);
            }
            std::cerr << "StreamSocket: input request pending!" << std::endl;
        }
    }

    StreamSocket::operator io::Channel () const
    {
            // Yes, ::SOCKET can be cast into ::HANDLE to use in calls to
            // ReadFile() and WriteFile()...
        const ::SOCKET socket = handle();
        return (io::Channel(Object::proxy(
            reinterpret_cast< ::HANDLE >(socket)
            )));
    }

} }
