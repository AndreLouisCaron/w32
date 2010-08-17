#ifndef _w32_net_tcp_Stream_hpp__
#define _w32_net_tcp_Stream_hpp__

/*!
 * @file w32/net/tcp/Stream.hpp
 * @author Andre Caron
 */

#include "../__configure__.hpp"
#include <w32/net/StreamSocket.hpp>
#include <w32/net/ipv4/EndPoint.hpp>
#include <w32/net/tcp/Listener.hpp>

namespace w32 { namespace net { namespace tcp {

        /*!
         * @brief Transfer Control Protocol, connection socket.
         */
    class W32_NET_EXPORT Stream :
        public StreamSocket
    {
        /* construction. */
    public:
            /*!
             * @brief Wait for a connection (server side).
             */
        Stream ( Listener& listener );

            /*!
             * @brief Connect to a server (client side).
             */
        Stream ( const ipv4::EndPoint& peer );
    };

} } }

#endif /* _w32_net_tcp_Stream_hpp__ */
