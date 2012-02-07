// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net/Socket.hpp>
#include <w32/Error.hpp>

namespace {

    void abandon ( ::SOCKET object ) {}
    void destroy ( ::SOCKET object )
    {
        if ( ::closesocket(object) != 0 )
        {
            const w32::Error error(::WSAGetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace net {

    Socket::Handle Socket::claim ( ::SOCKET object )
    {
        return (Handle(object, &::destroy));
    }

    Socket::Handle Socket::proxy ( ::SOCKET object )
    {
        return (Handle(object, &::abandon));
    }

    Socket::Socket ( Handle handle )
        : myHandle(handle)
    {
    }

    Socket::~Socket ()
    {
    }

    const Socket::Handle& Socket::handle () const
    {
        return (myHandle);
    }

    void Socket::blocking ( bool blocking )
    {
        ::u_long value = blocking? 0 : 1;
        const int result = ::ioctlsocket(handle(), FIONBIO, &value);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(ioctlsocket, error);
        }
    }

    ulong Socket::available () const
    {
        ::u_long value = 0;
        const int result = ::ioctlsocket(handle(), FIONREAD, &value);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(ioctlsocket, error);
        }
        return (value);
    }

    void Socket::shutdown ()
    {
        shutdown(Shutdown::output());
    }

    void Socket::shutdown ( const Shutdown& method )
    {
        const int result = ::shutdown(handle(), method.value());
        if ( result != 0 )
        {
            const int error = ::WSAGetLastError();
            if (error == WSAECONNABORTED) {
                return;
            }
            if (error == WSAECONNRESET) {
                return;
            }
            UNCHECKED_WIN32C_ERROR(shutdown, error);
        }
    }

    void Socket::select ( mt::ManualResetEvent& event, Event events )
    {
        const int result = ::WSAEventSelect(handle(), event.handle(), events);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(WSAEventSelect, error);
        }
    }

    const Socket::Type Socket::Type::stream ()
    {
        return (SOCK_STREAM);
    }

    const Socket::Type Socket::Type::dgram ()
    {
        return (SOCK_DGRAM);
    }

    const Socket::Type Socket::Type::raw ()
    {
        return (SOCK_RAW);
    }

    const Socket::Type Socket::Type::rdm ()
    {
        return (SOCK_RDM);
    }

    const Socket::Type Socket::Type::seqpacket ()
    {
        return (SOCK_SEQPACKET);
    }

    Socket::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Socket::Type::Value Socket::Type::value () const
    {
        return (myValue);
    }

    const Socket::Shutdown Socket::Shutdown::output ()
    {
        return (SD_SEND);
    }

    const Socket::Shutdown Socket::Shutdown::input ()
    {
        return (SD_RECEIVE);
    }

    const Socket::Shutdown Socket::Shutdown::both ()
    {
        return (SD_BOTH);
    }

    Socket::Shutdown::Shutdown ( Value value )
        : myValue(value)
    {
    }

    Socket::Shutdown::Value Socket::Shutdown::value () const
    {
        return (myValue);
    }

} }
