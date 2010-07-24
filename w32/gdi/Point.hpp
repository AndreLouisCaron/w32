#ifndef _w32_gdi_Point_hpp__
#define _w32_gdi_Point_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace gdi {

    class W32_GDI_EXPORT Point
    {
        /* nested types. */
    public:
        typedef ::POINT Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Point () {
            myData.x = 0, myData.y = 0;
        }

        Point ( long x, long y ) {
            myData.x = x, myData.y = y;
        }

        Point ( const Data& value )
            : myData(value)
        {}

        /* methods. */
    public:
        Data& data () {
            return (myData);
        }

        const Data& data () const {
            return (myData);
        }

        void x ( long value ) {
            myData.x = value;
        }

        long x () const {
            return (myData.x);
        }

        void y ( long value ) {
            myData.y = value;
        }

        long y () const {
            return (myData.y);
        }
    };

} }

#endif /* _w32_gdi_Point_hpp__ */
