#ifndef _w32_net_ipv4_EndPoint_hpp__
#define _w32_net_ipv4_EndPoint_hpp__

/*!
 * @file w32/net/ipv4/EndPoint.hpp
 * @author Andre Caron
 */

#include "../__configure__.hpp"
#include <w32/net/integers.hpp>
#include <w32/net/Context.hpp>
#include <w32/net/ipv4/Address.hpp>
#include <iosfwd>

namespace w32 { namespace net { namespace ipv4 {

        /*!
         * @brief Internet Protocol address (including port) version 4.
         */
    class EndPoint
    {
        /* nested types. */
    public:
        typedef ::sockaddr_in Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        EndPoint ();
        EndPoint ( const Data& address );
        EndPoint ( uint32 address, uint16 port );
        EndPoint ( uint8 b1, uint8 b2, uint8 b3, uint8 b4, uint16 port );
        EndPoint ( const Address& address, uint16 port );
        EndPoint ( const EndPoint& other );

        /* methods. */
    public:
        int size () const;
        ::sockaddr * raw ();
        const ::sockaddr * raw () const;
        Data& data ();
        const Data& data () const;
        uint16 port () const;
        Address address () const;
    };

    std::ostream& operator<<
        ( std::ostream& out, const EndPoint& value );

} } }

#endif /* _w32_net_ipv4_EndPoint_hpp__ */
