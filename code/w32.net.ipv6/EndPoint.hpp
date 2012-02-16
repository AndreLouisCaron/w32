#ifndef _w32_net_ipv6_EndPoint_hpp__
#define _w32_net_ipv6_EndPoint_hpp__

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
 * @file w32.net.ipv6/EndPoint.hpp
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
