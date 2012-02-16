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
 * @file w32.net.ipv6/Address.cpp
 * @author Andre Caron
 */

#include <w32.net.ipv6/Address.hpp>
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
