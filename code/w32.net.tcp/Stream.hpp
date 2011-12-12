#ifndef _w32_net_tcp_Stream_hpp__
#define _w32_net_tcp_Stream_hpp__

/*!
 * @file w32/net/tcp/Stream.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32.net/StreamSocket.hpp>
#include <w32.net.ipv4/EndPoint.hpp>
#include <w32.net.tcp/Listener.hpp>

namespace w32 { namespace io {

    class InputStream;
    class OutputStream;
    class Stream;

} }

namespace w32 { namespace net { namespace tcp {

        /*!
         * @brief Transfer Control Protocol, connection socket.
         */
    class Stream :
        public StreamSocket
    {
        /* construction. */
    public:
            /*!
             * @brief Wait for a connection (server side).
             */
        Stream ( Listener& listener );
        Stream ( Listener& listener, ipv4::EndPoint& peer );

            /*!
             * @brief Connect to a server (client side).
             */
        Stream ( const ipv4::EndPoint& peer );

        /* operators . */
    public:
        operator io::Stream () const;
        operator io::InputStream () const;
        operator io::OutputStream () const;
    };

} } }

#endif /* _w32_net_tcp_Stream_hpp__ */
