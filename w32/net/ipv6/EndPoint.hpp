#ifndef _win32c_net_ipv6_EndPoint_hpp__
#define _win32c_net_ipv6_EndPoint_hpp__

/*!
 * @file EndPoint.hpp
 * @author Andre Caron
 */

#include <win32c/net/integers.hpp>
#include <win32c/net/Context.hpp>
#include <win32c/net/ipv6/Address.hpp>
#include <iosfwd>

namespace win32c { namespace net { namespace ipv6 {

        /*!
         * @brief Internet Protocol address (including port) version 6.
         */
    class EndPoint
    {
        /* nested types. */
    public:
        ::sockaddr_in6 Value;

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

#endif /* _win32c_net_ipv6_EndPoint_hpp__ */
