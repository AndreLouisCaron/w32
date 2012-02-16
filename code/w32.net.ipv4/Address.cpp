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

/*!
 * @file w32.net.ipv4/Address.cpp
 * @author Andre Caron
 */

#include <w32.net.ipv4/Address.hpp>
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

    const Address Address::local ()
    {
        return (Address(127,0,0,1));
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

    uint8 Address::_1 () const
    {
        return (myValue.S_un.S_un_b.s_b1);
    }

    uint8 Address::_2 () const
    {
        return (myValue.S_un.S_un_b.s_b2);
    }

    uint8 Address::_3 () const
    {
        return (myValue.S_un.S_un_b.s_b3);
    }

    uint8 Address::_4 () const
    {
        return (myValue.S_un.S_un_b.s_b4);
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

    std::istream& operator>> ( std::istream& in, Address& address )
    {
          // Clear, just to make sure.
        address = Address::none();
        
          // Parse 4 integer parts.
        int parts[4];
        for ( int i = 0; ((i < 4) && in); ++i )
        {
            if ((i > 0) && ((in.peek() != '.') || !in.ignore(1))) {
                in.setstate(std::ios::failbit); return (in);
            }
            if ( !(in >> parts[i]) || (parts[i] < 0) || (parts[i] > 255)) {
                in.setstate(std::ios::failbit); return (in);
            }
        }
        
          // Succeeded, save results.
        address.myValue.S_un.S_un_b.s_b1 = parts[0];
        address.myValue.S_un.S_un_b.s_b2 = parts[1];
        address.myValue.S_un.S_un_b.s_b3 = parts[2];
        address.myValue.S_un.S_un_b.s_b4 = parts[3];
        
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
