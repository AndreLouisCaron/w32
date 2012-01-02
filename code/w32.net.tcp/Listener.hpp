#ifndef _w32_net_tcp_Listener_hpp__
#define _w32_net_tcp_Listener_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net/Socket.hpp>
#include <w32.net.ipv4/EndPoint.hpp>

namespace w32 { namespace net { namespace tcp {

    /*!
     * @ingroup w32-net
     * @brief Transfer control protocol "server" socket.
     */
    class Listener :
        public Socket
    {
        /* construction. */
    public:
        explicit Listener ( const Socket::Handle& handle );
        Listener ( const ipv4::EndPoint& name, int backlog = SOMAXCONN );
    };

} } }

#endif /* _w32_net_tcp_Listener_hpp__ */
