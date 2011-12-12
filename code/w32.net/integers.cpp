// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
