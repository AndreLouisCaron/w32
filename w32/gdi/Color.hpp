#ifndef _w32_gdi_Color_hpp__
#define _w32_gdi_Color_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace gdi {

        /*!
         * @brief Wraps a (red,green,blue) triplet color value.
         */
    class Color
    {
        /* nested types. */
    public:
        typedef ::COLORREF Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Color ()
            : myValue(RGB(0,0,0))
        {}

        Color ( const byte& r, const byte& g, const byte& b )
            : myValue(RGB(r,g,b))
        {}

        Color ( const Value& value )
            : myValue(value)
        {}

        /* methods. */
    public:
        Value& value () {
            return (myValue);
        }

        const Value& value () const {
            return (myValue);
        }
    };

} }

#endif /* _w32_gdi_Color_hpp__ */
