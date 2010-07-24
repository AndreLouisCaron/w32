#ifndef _w32_net_DatagramSocket_hpp__
#define _w32_net_DatagramSocket_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/net/Socket.hpp>
#include <w32/net/ipv4/EndPoint.hpp>

namespace w32 { namespace net {

    class W32_NET_EXPORT DatagramSocket :
        public Socket
    {
        /* construction. */
    protected:
        DatagramSocket ( Handle handle );

        /* methods. */
    protected:
        int put (
            const void * peer, int size, const void * buffer, int length );
        int get ( void * peer, int size, void * buffer, int length );
    };

} }

#endif /* _w32_net_DatagramSocket_hpp__ */
