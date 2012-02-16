#ifndef _w32_net_Family_hpp__
#define _w32_net_Family_hpp__

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
#include <iosfwd>

namespace w32 { namespace net {

    class Host;

        /*!
         * @brief Enumeration of address families.
         */
    class Family
    {
        /* nested types. */
    public:
            /*!
             * @brief Native representation of the enumeration.
             */
        typedef int Value;

        /* class data. */
    public:
        static const Family unspecified ();
        static const Family netbios ();
        static const Family inet4 ();
        static const Family inet6 ();
        static const Family irda ();
        static const Family bluetooth ();

        /* class methods. */
    public:
            /*!
             * @brief Extracts the address family used to connect to a host.
             *
             * @note You might want to use the Host::family() function instead
             *   of this one as it provides a simpler syntax.
             */
        static Family of ( const Host& host );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only!
        Family ( Value value );

        /* methods. */
    public:
            /*!
             * @brief Obtains the enumeration value's native representation.
             */
        Value value () const;
    };

    bool operator== ( const Family& lhs, const Family& rhs );
    bool operator!= ( const Family& lhs, const Family& rhs );

    std::ostream& operator<<
        ( std::ostream& out, const Family& family );

} }

#endif /* _w32_net_Family_hpp__ */
