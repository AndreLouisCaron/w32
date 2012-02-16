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

#include <w32.net/integers.hpp>
#include <iostream>

namespace w32 { namespace net {

    uint16::uint16 ( w32::uint16 raw )
        : myValue(::htons(raw))
    {
    }

    uint16::uint16 ( const box& data )
        : myValue(data.value())
    {
    }

    w32::uint16 uint16::raw () const
    {
        return (myValue);
    }

    uint16::operator w32::uint16 () const
    {
        return (::ntohs(myValue));
    }

    bool operator== ( const uint16& lhs, const uint16& rhs )
    {
        return (lhs.raw() == rhs.raw());
    }

    bool operator!= ( const uint16& lhs, const uint16& rhs )
    {
        return (lhs.raw() != rhs.raw());
    }

    std::ostream& operator<< ( std::ostream& out, const uint16& value )
    {
        return (out << (w32::uint16)value);
    }

    uint16::box::box ( w32::uint16 value )
        : myValue(value)
    {
    }

    w32::uint16 uint16::box::value () const
    {
        return (myValue);
    }

    uint32::uint32 ( w32::uint32 raw )
        : myValue(::htonl(raw))
    {
    }

    uint32::uint32 ( const box& data )
        : myValue(data.value())
    {
    }

    w32::uint32 uint32::raw () const
    {
        return (myValue);
    }

    uint32::operator w32::uint32 () const
    {
        return (::ntohl(myValue));
    }

    bool operator== ( const uint32& lhs, const uint32& rhs )
    {
        return (lhs.raw() == rhs.raw());
    }

    bool operator!= ( const uint32& lhs, const uint32& rhs )
    {
        return (lhs.raw() != rhs.raw());
    }

    std::ostream& operator<< ( std::ostream& out, const uint32& value )
    {
        return (out << (w32::uint32)value);
    }

    uint32::box::box ( w32::uint32 value )
            : myValue(value)
    {
    }

    w32::uint32 uint32::box::value () const
    {
        return (myValue);
    }

} }
