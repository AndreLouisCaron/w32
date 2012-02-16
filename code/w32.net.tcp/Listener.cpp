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
