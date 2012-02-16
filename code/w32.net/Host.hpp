#ifndef _w32_net_Host_hpp__
#define _w32_net_Host_hpp__

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
#include <w32/astring.hpp>
#include <w32/mstring.hpp>
#include <w32/string.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32.net/Context.hpp>
#include <w32.net/Family.hpp>

namespace w32 { namespace net {

    using std::bad_cast;

    /*!
     * @ingroup w32-net
     */
    class Host
    {
        /* nested types. */
    public:
        class Aliases;

        typedef ::hostent Data;

        /* class methods. */
    private:
        static const ::hostent * fetch
            ( const void * data, int size, int type );

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Host ();
        explicit Host ( const astring& name );
        explicit Host ( const string& name );

        template<typename Address>
        explicit Host ( const Address& address )
        {
            const ::hostent * data = Host::fetch
                (&address.value(), sizeof(address.value()), Address::family());
            ::memcpy(&myData, data, sizeof(myData));
        }

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

    class Host::Aliases :
        public mstring
    {
        /* construction. */
    public:
        explicit Aliases ( const Host& host );
    };

} }

#endif /* _w32_net_Host_hpp__ */
