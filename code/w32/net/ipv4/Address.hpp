#ifndef _w32_net_ipv4_Address_hpp__
#define _w32_net_ipv4_Address_hpp__

/*!
 * @file w32/net/ipv4/Address.hpp
 * @author Andre Caron
 */

#include "../__configure__.hpp"
#include <w32/astring.hpp>
#include <w32/net/integers.hpp>
#include <w32/net/Family.hpp>
#include <iosfwd>

namespace w32 { namespace net { namespace ipv4 {

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
