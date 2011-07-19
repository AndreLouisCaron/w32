#ifndef _w32_Time_hpp__
#define _w32_Time_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 {

    class Time
    {
        /* nested types. */
    public:
        typedef ::SYSTEMTIME Data;

        /* data. */
    private:
        Data myData;

        /* class methods. */
    public:
        static Time now ();

        /* construction. */
    public:
        Time ();
        Time ( const Data& value );
        Time ( const ::FILETIME& value );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        word year () const;
        word month () const;
        word day () const;
        word hour () const;
        word minute () const;
        word second () const;
        word millisecond () const;
    };

}

#endif /* _w32_Time_hpp__ */
