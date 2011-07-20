/*!
 * @file Address.cpp
 * @author Andre Caron
 */

#include <w32/net/ipv6/Address.hpp>
#include <iomanip>

namespace w32 { namespace net { namespace ipv6 {

    const Family Address::family ()
    {
        return (Family::inet6());
    }

    Address::Address ( const Value& value )
        : myValue(value)
    {
    }

    Address::Value& Address::value ()
    {
        return (myValue);
    }

    const Address::Value& Address::value () const
    {
        return (myValue);
    }

    std::ostream& operator<< ( std::ostream& out, const Address& address )
    {
        const Address::Value& value = address.value();
        out << std::hex;
        for ( std::size_t i = 0; (i < 8); ++i ) {
            out << std::setfill('0') << std::setw(4) << (int)value.u.Word[i];
        }
        return (out << std::dec);
    }

} } }
