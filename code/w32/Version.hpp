#ifndef _w32_Version_hpp__
#define _w32_Version_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/string.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Operating system version.
     */
    class Version
    {
        /* nested types. */
    public:
        typedef ::OSVERSIONINFOEXW Data;

        /* class methods. */
    public:
        static Version _2000 ();
        static Version xp ();
        static Version vista ();

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Version ();
        Version ( dword major, dword minor );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        dword major () const;
        dword minor () const;
        dword build () const;

        /* operators. */
    public:
        bool operator== ( const Version& rhs ) const;
        bool operator< ( const Version& rhs ) const;
    };

}

#endif /* _w32_Version_hpp__ */
