#ifndef _w32_gdi_UpDown_hpp__
#define _w32_gdi_UpDown_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"
#include <w32.gdi/Control.hpp>

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
