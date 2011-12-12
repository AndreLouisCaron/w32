#ifndef _w32_net_Family_hpp__
#define _w32_net_Family_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
