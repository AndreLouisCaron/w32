#ifndef _w32_gdi_UpDown_hpp__
#define _w32_gdi_UpDown_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>

namespace w32 { namespace gdi {

    class Rectangle;
    class Window;

        /*!
         * @brief Control to select values in a range.
         */
    class UpDown :
        public Control
    {
      /* nested types. */
    public:
        class Range;

        /* construction. */
    public:
        explicit UpDown ( const Handle& handle );
        UpDown ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
        int base ( int radix );
        int base () const;
        int position ( int value );
        int position () const;
        void range ( const Range& range );
        Range range () const;
    };

    class UpDown::Range
    {
        /* data. */
    private:
        int myLow;
        int myHigh;

        /* construction. */
    public:
        Range ()
            : myLow(0), myHigh(0)
        {}

        Range ( int low, int high )
            : myLow(low), myHigh(high)
        {}

        /* methods. */
    public:
        int low () const {
            return (myLow);
        }

        void low ( int value ) {
            myLow = value;
        }

        int high () const {
            return (myHigh);
        }

        void high ( int value ) {
            myHigh = value;
        }
    };

} }

#endif /* _w32_gdi_UpDown_hpp__ */
