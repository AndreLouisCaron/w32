#ifndef _w32_net_integers_hpp__
#define _w32_net_integers_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/net/Context.hpp>
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
