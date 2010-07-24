#ifndef _win32c_net_ipv6_Address_hpp__
#define _win32c_net_ipv6_Address_hpp__

/*!
 * @file Address.hpp
 * @author Andre Caron
 */

#include "../__configure__.hpp"
#include <w32/net/integers.hpp>
#include <w32/net/Family.hpp>
#include <iosfwd>

namespace w32 { namespace net { namespace ipv6 {

    class W32_NET_EXPORT Address
    {
        /* nested types. */
    public:
        typedef ::in6_addr Value;

        /* class data. */
    public:
        static const Family family ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        explicit Address ( const Value& value );

        /* methods. */
    public:
        Value& value ();
        const Value& value () const;
    };

    bool operator== ( const Address& lhs, const Address& rhs );
    bool operator!= ( const Address& lhs, const Address& rhs );

    W32_NET_EXPORT
        std::istream& operator<< ( std::istream& in, Address& address );

    W32_NET_EXPORT
        std::ostream& operator<< ( std::ostream& out, const Address& address );

} } }

#endif /* _win32c_net_ipv6_Address_hpp__ */
