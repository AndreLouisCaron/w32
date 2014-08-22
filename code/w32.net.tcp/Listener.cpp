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

    static Listener::AcceptEx
        lookup_accept_ex (::SOCKET handle)
     {
         // TODO: figure out from which SDK version 'AcceptEx()'
         //       is suitably declared in the SDK headers.
#if 0
         return (&::AcceptEx);
#else
         ::LPFN_ACCEPTEX value = 0;
         ::GUID field = WSAID_ACCEPTEX;
         ::DWORD size = 0;
         const int status = ::WSAIoctl(
             handle, SIO_GET_EXTENSION_FUNCTION_POINTER,
             &field, sizeof(field), &value, sizeof(value), &size, NULL, NULL);
         if (status == SOCKET_ERROR) {
             const int error = ::WSAGetLastError();
             UNCHECKED_WIN32C_ERROR(WSAIoctl, error);
         }
         return (value);
#endif
     }

    static Listener::GetAcceptExSockAddrs
        lookup_get_accept_ex_sock_addrs (::SOCKET handle)
    {
         // TODO: figure out from which SDK version 'AcceptEx()'
         //       is suitably declared in the SDK headers.
#if 0
         return (&::GetAcceptExSockAddrs);
#else
         ::LPFN_GETACCEPTEXSOCKADDRS value = 0;
         ::GUID field = WSAID_GETACCEPTEXSOCKADDRS;
         ::DWORD size = 0;
         const int status = ::WSAIoctl(
             handle, SIO_GET_EXTENSION_FUNCTION_POINTER,
             &field, sizeof(field), &value, sizeof(value), &size, NULL, NULL);
         if (status == SOCKET_ERROR) {
             const int error = ::WSAGetLastError();
             UNCHECKED_WIN32C_ERROR(WSAIoctl, error);
         }
         return (value);
#endif
    }

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

    Listener::AcceptEx Listener::accept_ex () const
    {
        return (lookup_accept_ex(handle()));
    }

    Listener::GetAcceptExSockAddrs Listener::get_accept_ex_sock_addrs() const
    {
        return (lookup_get_accept_ex_sock_addrs(handle()));
    }

    bool Listener::cancel (::OVERLAPPED& xfer)
    {
        const ::SOCKET socket = this->handle();
        const ::HANDLE handle = reinterpret_cast<::HANDLE>(socket);
        const ::BOOL result = ::CancelIoEx(handle, &xfer);
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            // May have already completed.
            if (error == ERROR_NOT_FOUND) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(CancelIoEx, error);
        }
        return (true);
    }

    bool Listener::cancel (io::Transfer& xfer)
    {
        return (cancel(xfer.data()));
    }

} } }
