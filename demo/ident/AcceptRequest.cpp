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
 * @file demo/ident/AcceptRequest.cpp
 */

#include "AcceptRequest.hpp"
#include <w32/Error.hpp>

namespace {

    net::Socket::Handle create_socket ()
    {
        const ::SOCKET result = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (result == INVALID_SOCKET) {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(socket, error);
        }
        return (net::Socket::claim(result));
    }

}

namespace idp {

    AcceptRequest::AcceptRequest ()
        : myStream(create_socket()),
          myBuffer(new Buffer(512))
    {
    }

    bool AcceptRequest::start ( tcp::Listener& listener )
    {
        myBuffer->clear();

        ::DWORD size = 0;
        const ::BOOL result = ::AcceptEx(
            listener.handle(), myStream, myBuffer->next(),
            myBuffer->left()-64, 32, 32, &size, &myTransfer.data());
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            if (error != ERROR_IO_PENDING) {
                UNCHECKED_WIN32C_ERROR(AcceptEx, error);
            }
        }
        myBuffer->gave(size);
        return (true);
    }

    void AcceptRequest::cancel ( tcp::Listener& listener )
    {
        const ::SOCKET socket = listener.handle();
        const ::HANDLE handle = reinterpret_cast<::HANDLE>(socket);
        const ::BOOL result = ::CancelIoEx(handle, &myTransfer.data());
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            // Ignore request if transfer has already completed.
            if (error != ERROR_NOT_FOUND) {
                UNCHECKED_WIN32C_ERROR(CancelIoEx, error);
            }
        }
    }

    void AcceptRequest::update_context ( tcp::Listener& listener )
    {
        ::SOCKET parent = listener.handle();
        const int level = SOL_SOCKET;
        const int option = SO_UPDATE_ACCEPT_CONTEXT;
        const int result = ::setsockopt
            (myStream, level, option,
             reinterpret_cast<char*>(&parent), sizeof(parent));
        if (result == SOCKET_ERROR) {
            std::cerr << "Could not update context." << std::endl;
        }
    }

    void AcceptRequest::recover_endpoints ( ipv4::EndPoint& host,
                                            ipv4::EndPoint& peer )
    {
        ::sockaddr * hdata = 0; int hsize = 0;
        ::sockaddr * pdata = 0; int psize = 0;
        ::GetAcceptExSockaddrs(myBuffer->data(),
                               myBuffer->capacity()-64, 32, 32,
                               &hdata, &hsize, &pdata, &psize);
        host = *reinterpret_cast<const ::sockaddr_in*>(hdata);
        peer = *reinterpret_cast<const ::sockaddr_in*>(pdata);
    }

    void AcceptRequest::reset ()
    {
        myTransfer.clear();
        myStream = create_socket();

        myBuffer = new Buffer(512);
    }

    // Access the buffer containing data received with the connection.
    // The completion notification contains the number of bytes in this
    // buffer actually correspond to data sent by the peer.
    Buffer * AcceptRequest::buffer ()
    {
        return (myBuffer);
    }

    // Access the socket.  Only connected once the callback is triggered.
    tcp::Stream AcceptRequest::stream () const
    {
        return (tcp::Stream(myStream));
    }

    bool AcceptRequest::started ( const io::Transfer& transfer ) const
    {
        return (&transfer.data() == &myTransfer.data());
    }

    bool AcceptRequest::started ( const ::OVERLAPPED& transfer ) const
    {
        return (&transfer == &myTransfer.data());
    }

}
