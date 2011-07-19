#ifndef _w32_Architecture_hpp__
#define _w32_Architecture_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 {

    class System;

    class Architecture
    {
        /* nested types. */
    public:
        typedef word Value;

        /* class data. */
    public:
        static const Architecture x64 ();
        static const Architecture ia64 ();
        static const Architecture x86 ();
        static const Architecture unknown ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Architecture ( Value value );

        /* class methods. */
    public:
        static Architecture of ( const System& system );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value() const;
        bool operator== ( const Architecture& other ) const;
        bool operator!= ( const Architecture& other ) const;
    };

}

#endif /* _w32_Architecture_hpp__ */
