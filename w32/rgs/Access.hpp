#ifndef _w32_rgs_Access_hpp__
#define _w32_rgs_Access_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace rgs {

        /*!
         * @brief Enumerates access types for registry keys.
         * @note The access is given when opening a registry key and only
         *   defines the access the given handle will allow you (i.e. this is
         *   not persistent.
         */
    class W32_RGS_EXPORT Access
    {
        /* nested types. */
    public:
        typedef ::REGSAM Value;

        /* class data. */
    public:
        static const Access list ();
        static const Access get ();
        static const Access set ();
        static const Access create ();
        static const Access read ();
        static const Access write ();
        static const Access all ();

        /* members. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Access ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        Access& operator|= ( const Access& other );
        Access operator| ( const Access& other ) const;
        Access& operator&= ( const Access& other );
        Access operator& ( const Access& other ) const;

        operator Value () const;
    };

} }

#endif /* _w32_rgs_Access_hpp__ */
