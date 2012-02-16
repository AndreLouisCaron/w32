#ifndef _w32_net_integers_hpp__
#define _w32_net_integers_hpp__

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

#include "__configure__.hpp"
#include <w32.net/Context.hpp>
#include <w32/types.hpp>
#include <iosfwd>

namespace w32 { namespace net {

        // Typedefs for unsigned types.
    typedef ::u_char uchar;
    typedef ::u_short ushort;
    typedef ::u_int uint;
    typedef ::u_long ulong;

        /*!
         * @brief Network byte-ordered 16 bit integer.
         */
    class uint16
    {
        /* nested types. */
    public:
        class box;

        /* data. */
    private:
        w32::uint16 myValue;

        /* construction. */
    public:
        uint16 ( w32::uint16 raw = 0 );
        uint16 ( const box& data );

        /* methods. */
    public:
        w32::uint16 raw () const;

        /* operators. */
    public:
        operator w32::uint16 () const;
    };

    bool operator== ( const uint16& lhs, const uint16& rhs );
    bool operator!= ( const uint16& lhs, const uint16& rhs );

    std::ostream& operator<< ( std::ostream& out, const uint16& value );

    class uint16::box
    {
        /* data. */
    private:
        w32::uint16 myValue;

        /* construction. */
    public:
        explicit box ( w32::uint16 value );

        /* methods. */
    public:
        w32::uint16 value () const;
    };

        /*!
         * @brief Network byte-ordered 32 bit integer.
         */
    class uint32
    {
        /* nested types. */
    public:
        class box;

        /* data. */
    private:
        w32::uint32 myValue;

        /* construction. */
    public:
        uint32 ( w32::uint32 raw = 0 );
        uint32 ( const box& data );

        /* methods. */
    public:
        w32::uint32 raw () const;

        /* operators. */
    public:
        operator w32::uint32 () const;
    };

    bool operator== ( const uint32& lhs, const uint32& rhs );
    bool operator!= ( const uint32& lhs, const uint32& rhs );

    std::ostream& operator<< ( std::ostream& out, const uint32& value );

    class uint32::box
    {
        /* data. */
    private:
        w32::uint32 myValue;

        /* construction. */
    public:
        explicit box ( w32::uint32 value );

        /* methods. */
    public:
        w32::uint32 value () const;
    };

} }

#endif /* _w32_net_integers_hpp__ */
