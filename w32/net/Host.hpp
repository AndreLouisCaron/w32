#ifndef _w32_net_Host_hpp__
#define _w32_net_Host_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/astring.hpp>
#include <w32/mstring.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32/net/Context.hpp>
#include <w32/net/Family.hpp>
#include <w32/net/ipv4/Address.hpp>
#include <w32/net/ipv6/Address.hpp>

namespace w32 { namespace net {

    using std::bad_cast;

    class W32_NET_EXPORT Host
    {
        /* nested types. */
    public:
        class Aliases;

        typedef ::hostent Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Host ();
        explicit Host ( const astring& name );
        explicit Host ( const ipv4::Address& address );
        explicit Host ( const ipv6::Address& address );

        /* methods. */
    public:
        const Data& data () const;

             /*!
              * @brief Obtains the address family of addresses in the host.
              */
        const Family family () const;

            /*!
             * @brief Counts the number of addresses in the address list.
             */
        size_t addresses () const;

            /*!
             * @brief Extracts an address from the address list.
             *
             * @throw std::bad_cast The @a index-th address is not of the
             *   requested type. To provide the right address type, look
             *   at the @c family() function.
             *
             * @see family
             * @see Family
             */
        template<typename Address>
        Address address ( size_t index ) const
        {
            typedef typename Address::Value Value;
            if ( Address::family() != family() ) {
                throw (std::bad_cast());
            }
            const void *const address = myData.h_addr_list[index];
            return (Address(*reinterpret_cast<const Value*>(address)));
        }

            /*!
             * @brief Obtains the fullly qualified name of the host.
             */
        astring name () const;
    };

    class W32_NET_EXPORT Host::Aliases :
        public mstring
    {
        /* construction. */
    public:
        explicit Aliases ( const Host& host );
    };

} }

#endif /* _w32_net_Host_hpp__ */
