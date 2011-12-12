#ifndef _w32_net_udp_Socket_hpp__
#define _w32_net_udp_Socket_hpp__

/*!
 * @file w32/net/udp/Socket.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32.net/DatagramSocket.hpp>

namespace w32 { namespace net { namespace udp {

    class Socket :
        public DatagramSocket
    {
        /* construction. */
    public:
        Socket ( const ipv4::EndPoint& host );

        /* methods. */
    public:
        int get ( ipv4::EndPoint& peer, void * buffer, int bytes );
        int put ( const ipv4::EndPoint& peer, const void * buffer, int bytes );

    protected:
        using DatagramSocket::get;
        using DatagramSocket::put;
    };

} } }

#endif /* _w32_net_udp_Socket_hpp__ */
