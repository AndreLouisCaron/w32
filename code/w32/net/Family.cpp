// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/Family.hpp>
#include <w32/net/Host.hpp>
#include <iostream>

namespace w32 { namespace net {

    const Family Family::unspecified ()
    {
        return (AF_UNSPEC);
    }

    const Family Family::netbios ()
    {
        return (AF_NETBIOS);
    }

    const Family Family::inet4 ()
    {
        return (AF_INET);
    }

    const Family Family::inet6 ()
    {
        return (AF_INET6);
    }

    const Family Family::irda ()
    {
        return (AF_IRDA);
    }

    const Family Family::bluetooth ()
    {
        return (AF_BTH);
    }

    Family Family::of ( const Host& host )
    {
        return (host.data().h_addrtype);
    }

    Family::Family ( Value value )
        : myValue(value)
    {
    }

    Family::Value Family::value () const
    {
        return (myValue);
    }

    bool operator== ( const Family& lhs, const Family& rhs )
    {
        return (lhs.value() == rhs.value());
    }

    bool operator!= ( const Family& lhs, const Family& rhs )
    {
        return (lhs.value() != rhs.value());
    }

    std::ostream& operator<< ( std::ostream& out, const Family& family )
    {
        switch ( family.value() )
        {
        case AF_UNSPEC:
            return (out << "unspecified");
        case AF_NETBIOS:
            return (out << "NetBIOS");
        case AF_INET:
            return (out << "IPv4");
        case AF_INET6:
            return (out << "IPv6");
        case AF_IRDA:
            return (out << "IrDA");
        case AF_BTH:
            return (out << "Bluetooth");
        default:
            {}
        }
        out.setstate(std::ios::failbit);
        return (out);
    }

} }
