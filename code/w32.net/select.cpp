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

#include <w32.net/select.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace net {

    void select ( Set& read, Set& write, Set& errors )
    {
        const int result = ::select(
            0, &read.data(), &write.data(), &errors.data(), 0
            );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(select, ::WSAGetLastError());
        }
    }

    bool select ( Set& read, Set& write, Set& errors, const Timespan& timeout )
    {
        const int result = ::select(
            0, &read.data(), &write.data(), &errors.data(), &timeout.value()
            );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(select, ::WSAGetLastError());
        }
        
            // Check if call timed-out!
        return (result > 0);
    }

    void select ( Set& sockets )
    {
        select(sockets, Timespan());
    }

    bool select ( Set& sockets, const Timespan& timeout )
    {
        const int result = ::select(
            0, &sockets.data(), 0, 0, &timeout.value()
            );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(select, ::WSAGetLastError());
        }
        
            // Check if call timed-out!
        return (result > 0);
    }

    bool readable ( const Socket& socket )
    {
        return (readable(socket, Timespan()));
    }

    bool readable ( const Socket& socket, const Timespan& timeout )
    {
        Set set; set.add(socket);
        
        const int result = ::select(
            0, &set.data(), 0, 0, &timeout.value()
            );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(select, ::WSAGetLastError());
        }
        
            // Check if call timed-out!
        return (result > 0);
    }

    bool writable ( const Socket& socket )
    {
        Set set; set.add(socket);
        const Timespan timeout;
        
        const int result = ::select(
            0, 0, &set.data(), 0, &timeout.value()
            );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(select, ::WSAGetLastError());
        }
        
            // Check if call timed-out!
        return (result > 0);
    }

} }
