#ifndef _w32_shl_Location_hpp__
#define _w32_shl_Location_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/shl/Path.hpp>

namespace w32 { namespace shl {

    class W32_SHL_EXPORT Location
    {
        /* nested types. */
    public:
        typedef int Value;

        /* class data. */
    public:
        static const Location computer ();
        static const Location desktop ();
        static const Location fonts ();
        static const Location programs ();
        static const Location start ();
        static const Location startup ();
        static const Location system ();
        static const Location windows ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Location ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
        operator Path () const;
    };

} }

#endif /* _w32_shl_LocationLocation_hpp__ */
