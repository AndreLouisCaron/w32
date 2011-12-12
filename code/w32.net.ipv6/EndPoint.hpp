#ifndef _w32_net_ipv6_EndPoint_hpp__
#define _w32_net_ipv6_EndPoint_hpp__

/*!
 * @file EndPoint.hpp
 * @author Andre Caron
 */

#include <w32.net/integers.hpp>
#include <w32.net/Context.hpp>
#include <w32.net.ipv6/Address.hpp>
#include <iosfwd>

namespace w32 { namespace net { namespace ipv6 {

        /*!
         * @brief Internet Protocol address (including port) version 6.
         */
    class EndPoint
    {
        /* nested types. */
    public:
        typedef ::sockaddr_in6 Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        EndPoint ();
        EndPoint ( const Value& address );

        /* methods. */
    public:
        Value& value ();
        const Value& value () const;
    };

    bool operator== ( const EndPoint& lhs, const EndPoint& rhs );
    bool operator!= ( const EndPoint& lhs, const EndPoint& rhs );

    std::ostream& operator<< ( std::ostream& out, const EndPoint& value );
    std::istream& operator<< ( std::istream& out, EndPoint& value );

} } }

#endif /* _w32_net_ipv6_EndPoint_hpp__ */
