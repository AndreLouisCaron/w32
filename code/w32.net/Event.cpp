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

#include <w32.net/Event.hpp>
#include <w32.net/Socket.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace net {

    const Event Event::accept ()
    {
        return (FD_ACCEPT);
    }

    const Event Event::connect ()
    {
        return (FD_CONNECT);
    }

    const Event Event::close ()
    {
        return (FD_CLOSE);
    }

    const Event Event::get ()
    {
        return (FD_READ);
    }

    const Event Event::put ()
    {
        return (FD_WRITE);
    }

    Event::Event ( Bitfield bits )
        : myBits(bits)
    {
    }

    Event::Bitfield Event::bits () const
    {
        return (myBits);
    }

    Event::operator Event::Bitfield () const
    {
        return (myBits);
    }

    Events::Events ( Socket& socket, mt::ManualResetEvent& event )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        const int result =
            ::WSAEnumNetworkEvents(socket.handle(), event.handle(), &myData);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(WSAEnumNetworkEvents, error);
        }
    }

    bool Events::operator& ( Event event ) const
    {
        return (((myData.lNetworkEvents & event) != 0)
            && (myData.iErrorCode[event] == 0));
    }

} }
