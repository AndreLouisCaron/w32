#ifndef _w32_Codepage_hpp__
#define _w32_Codepage_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 {

    class W32_CORE_EXPORT Codepage
    {
        /* nested types. */
    public:
        typedef uint Value;

        /* class data. */
    public:
        static const Codepage ansi ();
        static const Codepage oem ();
        static const Codepage utf7 ();
        static const Codepage utf8 ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Codepage ( Value value );

        /* methods. */
    public:
        Value value () const;
        bool valid () const;

        /* operators. */
    public:
        operator Value () const;

        bool operator== ( const Codepage& ) const;
        bool operator!= ( const Codepage& ) const;
    };

}

#endif /* _w32_Codepage_hpp__ */
