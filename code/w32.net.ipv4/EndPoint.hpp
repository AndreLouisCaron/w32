#ifndef _w32_net_ipv4_EndPoint_hpp__
#define _w32_net_ipv4_EndPoint_hpp__

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
 * @file w32.net.ipv4/EndPoint.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32.net/integers.hpp>
#include <w32.net/Context.hpp>
#include <w32.net.ipv4/Address.hpp>
#include <iosfwd>

namespace w32 { namespace net {

    class StreamSocket;

} }

namespace w32 { namespace net { namespace ipv4 {

    /*!
     * @ingroup w32-net
     * @brief Internet Protocol address (including port) version 4.
     */
    class EndPoint
    {
        /* nested types. */
    public:
        typedef ::sockaddr_in Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        EndPoint ();
        EndPoint ( const Data& data );
        EndPoint ( uint32 address, uint16 port );
        EndPoint ( uint8 b1, uint8 b2, uint8 b3, uint8 b4, uint16 port );
        EndPoint ( const Address& address, uint16 port );
        EndPoint ( const EndPoint& other );

        /* methods. */
    public:
        int size () const;
        ::sockaddr * raw ();
        const ::sockaddr * raw () const;
        Data& data ();
        const Data& data () const;
        uint16 port () const;
        Address address () const;

        /* operators. */
    public:
        EndPoint& operator= ( const Data& data );
    };

    EndPoint host ( const StreamSocket& socket );
    EndPoint peer ( const StreamSocket& socket );

    std::istream& operator>>
        ( std::istream& in, EndPoint& value );

    std::ostream& operator<<
        ( std::ostream& out, const EndPoint& value );

} } }

#endif /* _w32_net_ipv4_EndPoint_hpp__ */
