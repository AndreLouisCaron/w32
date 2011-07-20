#ifndef _w32_rgs_Values_hpp__
#define _w32_rgs_Values_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/rgs/Key.hpp>

namespace w32 { namespace rgs {

        /*!
         * @brief Enumerates a given key's values.
         */
    class Values :
        private NotCopyable
    {
        /* data. */
    private:
        const Key myKey;
        dword myIndex;
        dword myType;
        wchar_t myName[256]; // The maximum name length is 16383...
        long myResult;

        /* construction. */
    public:
        Values ( const Key& key );

        /* methods. */
    public:
        const Key& key () const;

            /*!
             * @brief Returns the name of the value found by @c next().
             * @note This is the empty string unless the last action performed
             *   was a call to @c next() that returned @c true.
             */
        const wchar_t * result () const;

            /*!
             * @brief Reaches the next value.
             * @note This invalides the string returned by @c result(), whether
             *   or not this function succeeds.
             * @return True if another value was found.
             */
        bool next ();
    };

} }

#endif /* _w32_rgs_Values_hpp__ */
