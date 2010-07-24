#ifndef _w32_gdi_Size_hpp__
#define _w32_gdi_Size_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace gdi {

    class W32_GDI_EXPORT Size
    {
        /* nested types. */
    public:
        typedef ::SIZE Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Size ()
        {
            myData.cx = 0, myData.cy = 0;
        }

        Size ( long width, long height )
        {
            myData.cx = width, myData.cy = height;
        }

        Size ( const Data& value )
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

        void width ( long value ) {
            myData.cx = value;
        }

        long width () const {
            return (myData.cx);
        }

        void height ( long value ) {
            myData.cy = value;
        }

        long height () const {
            return (myData.cy);
        }
    };

} }

#endif /* _w32_gdi_Size_hpp__ */
