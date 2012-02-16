// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <w32.net/Family.hpp>
#include <w32.net/Host.hpp>
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
