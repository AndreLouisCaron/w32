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

    ::HANDLE as_handle ( ::SOCKET object )
    {
        return (reinterpret_cast< ::HANDLE >(object));
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

    void Socket::dontlinger ()
    {
        ::LINGER data;
        data.l_onoff  = 0;
        data.l_linger = 0;

        const int result = ::setsockopt(handle(), SOL_SOCKET, SO_LINGER,
                                        reinterpret_cast<const char*>(&data),
                                        sizeof(data));
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(setsockopt, error);
        }
    }

    void Socket::linger ( w32::uint16 seconds )
    {
        ::LINGER data;
        data.l_onoff  = 1;
        data.l_linger = seconds;

        const int result = ::setsockopt(handle(), SOL_SOCKET, SO_LINGER,
                                        reinterpret_cast<const char*>(&data),
                                        sizeof(data));
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(setsockopt, error);
        }
    }

    ::LPFN_DISCONNECTEX Socket::disconnect_ex () const
    {
        ::GUID extension = WSAID_DISCONNECTEX;
        int ioctlcode SIO_GET_EXTENSION_FUNCTION_POINTER;

        ::LPFN_DISCONNECTEX data = 0;
        ::DWORD size = 0;

        const int result = ::WSAIoctl(handle(), ioctlcode, &extension,
                                      sizeof(extension), &data,
                                      sizeof(data), &size, 0, 0);
        if (result == SOCKET_ERROR)
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(WSAIoctl, error);
        }
        return (data);
    }

    void Socket::disconnect ( bool reuse )
    {
        ::LPFN_DISCONNECTEX DisconnectEx = disconnect_ex();

        const ::DWORD flags = reuse? TF_REUSE_SOCKET : 0;
        const ::BOOL result = DisconnectEx(handle(), 0, flags, 0);
        if ( result == FALSE )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(DisconnectEx, error);
        }
    }

    bool Socket::disconnect ( io::Transfer& transfer, bool reuse )
    {
        return (disconnect(transfer.data(), reuse));
    }

    bool Socket::disconnect ( ::OVERLAPPED& transfer, bool reuse )
    {
        ::LPFN_DISCONNECTEX DisconnectEx = disconnect_ex();

        const ::DWORD flags = reuse? TF_REUSE_SOCKET : 0;
        const ::BOOL result = DisconnectEx(handle(), &transfer, flags, 0);
        if ( result == FALSE )
        {
            const int error = ::WSAGetLastError();
            if ( error == ERROR_IO_PENDING ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(DisconnectEx, error);
        }
        return (true);
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
