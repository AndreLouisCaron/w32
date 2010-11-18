/*!
 * @file w32/net/ipv4/Address.cpp
 * @author Andre Caron
 */

#include <w32/net/ipv4/Address.hpp>
#include <iostream>

namespace w32 { namespace net { namespace ipv4 {

    const Family Address::family ()
    {
        return (Family::inet4());
    }

    const Address Address::none ()
    {
        return (INADDR_NONE);
    }

    const Address Address::any ()
    {
        return (INADDR_ANY);
    }

    const Address Address::broadcast ()
    {
        return (INADDR_BROADCAST);
    }

    Address::Address ()
    {
        myValue.S_un.S_addr = ::inet_addr(0);
    }

    Address::Address ( const astring& value )
    {
        myValue.S_un.S_addr = ::inet_addr(value.c_str());
    }

    Address::Address ( uint32 value )
    {
        myValue.S_un.S_addr = value;
    }

    Address::Address ( uint8 b1, uint8 b2, uint8 b3, uint8 b4 )
    {
        myValue.S_un.S_un_b.s_b1 = b1;
        myValue.S_un.S_un_b.s_b2 = b2;
        myValue.S_un.S_un_b.s_b3 = b3;
        myValue.S_un.S_un_b.s_b4 = b4;
    }

    Address::Address ( const Value& value )
        : myValue(value)
    {
    }

    const Address::Value& Address::value () const
    {
        return (myValue);
    }

    bool operator== ( const Address& lhs, const Address& rhs )
    {
        return (lhs.value().S_un.S_addr == rhs.value().S_un.S_addr);
    }

    bool operator< ( const Address& lhs, const Address& rhs )
    {
        return (lhs.value().S_un.S_addr < rhs.value().S_un.S_addr);
    }

    bool operator!= ( const Address& lhs, const Address& rhs )
    {
        return (lhs.value().S_un.S_addr != rhs.value().S_un.S_addr);
    }

    std::istream& operator<< ( std::istream& in, Address& address )
    {
            // Clear, just to make sure.
        address = Address::none();
        
        // Parse.
        
            // Check for successful parsing.
        if ( address == Address::none() ) {
            in.setstate(std::ios::failbit);
        }
        return (in);
    }

    std::ostream& operator<< ( std::ostream& out, const Address& address )
    {
        const Address::Value& value = address.value();
        return (out
            << (int)value.S_un.S_un_b.s_b1 << '.'
            << (int)value.S_un.S_un_b.s_b2 << '.'
            << (int)value.S_un.S_un_b.s_b3 << '.'
            << (int)value.S_un.S_un_b.s_b4);
    }

} } }
