// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
