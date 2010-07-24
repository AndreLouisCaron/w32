#ifndef _w32_rgs_Value_hpp__
#define _w32_rgs_Value_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/rgs/Key.hpp>
#include <w32/rgs/Type.hpp>

namespace w32 { namespace rgs {

        /*!
         * @brief Allows manipulation of registry key values.
         *
         * @todo Only handles strings and dwords for now.
         */
    class W32_RGS_EXPORT Value
    {
        /* data. */
    private:
        const Key myKey;
        const string myName;

        /* construction. */
    public:
            /*!
             * @Opens the value under @c key named @name.
             *
             * The key does not need to exist before hand. For queries, an error
             * is raised when querying the value's type or it's data. To write,
             * the registry creates the value on the fly. Also, the type is
             * changed to whatever you set it with no matter what it was before
             * hand.
             */
        Value ( const Key& key, const string& name );
        Value (
            const Key& key, const string& name, const string& value
            );

        /* operators. */
    public:
        const Key& key () const;
        const string& name () const;
            /*!
             * @brief Returns the type of value.
             */
        Type type () const;
        Value& operator= ( const string& value );
        operator const string () const;
        Value& operator= ( const dword& data );
    };

} }

#endif /* _w32_rgs_Value_hpp__ */
