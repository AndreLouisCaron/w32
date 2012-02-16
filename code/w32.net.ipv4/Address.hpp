#ifndef _w32_net_ipv4_Address_hpp__
#define _w32_net_ipv4_Address_hpp__

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
 * @file w32.net.ipv4/Address.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32/astring.hpp>
#include <w32.net/integers.hpp>
#include <w32.net/Family.hpp>
#include <iosfwd>

namespace w32 { namespace net { namespace ipv4 {

    /*!
     * @ingroup w32-net
     */
    class Address
    {
        /* nested types. */
    public:
        typedef ::in_addr Value;

        /* class data. */
    public:
        static const Family family ();

        static const Address none ();
        static const Address any ();
        static const Address broadcast ();
        static const Address local ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Address ();
        explicit Address ( const astring& value );
        Address ( uint32 value );
        Address ( uint8 b1, uint8 b2, uint8 b3, uint8 b4 );
        Address ( const Value& value );

        /* methods. */
    public:
        const Value& value () const;
        uint8 _1 () const;
        uint8 _2 () const;
        uint8 _3 () const;
        uint8 _4 () const;

        /* operators. */
    public:
        friend std::istream& operator>>
            ( std::istream& in, Address& address );
    };

    bool operator==
        ( const Address& lhs, const Address& rhs );

    bool operator!=
        ( const Address& lhs, const Address& rhs );

    bool operator<
        ( const Address& lhs, const Address& rhs );

    std::ostream& operator<<
        ( std::ostream& out, const Address& address );

} } }

#endif /* _w32_net_ipv4_Address_hpp__ */
