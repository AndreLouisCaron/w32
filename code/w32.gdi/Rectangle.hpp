#ifndef _win32c_gdi_Rectangle_hpp__
#define _win32c_gdi_Rectangle_hpp__

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
#include <w32.gdi/Point.hpp>
#include <w32.gdi/Size.hpp>

namespace w32 { namespace gdi {

    class Rectangle
    {
        /* nested types. */
    public:
        typedef ::RECT Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Rectangle () {
            ::ZeroMemory(&myData,sizeof(myData));
        }

        Rectangle ( long left, long right, long top, long bottom )
        {
            myData.left   = left;
            myData.right  = right;
            myData.top    = top;
            myData.bottom = bottom;
        }

        Rectangle ( const Point& origin, const Size& span )
        {
            myData.left   = origin.x();
            myData.right  = myData.left + span.width();
            myData.top    = origin.y();
            myData.bottom = myData.top + span.height();
        }

        Rectangle ( const Data& value )
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

            // Upper left.
        Point center () const {
            return (Point(left()+width()/2,top()+height()/2));
        }

            // Upper left.
        Point origin () const {
            return (Point(left(),top()));
        }

        void origin ( const Point& origin ) {
            left(origin.x()); top(origin.y());
        }

            // Goes down and to the right.
        Size span () const {
            return (Size(width(),height()));
        }

        long left () const {
            return (myData.left);
        }

        void left ( long value ) {
            myData.left = value;
        }

        long top () const {
            return (myData.top);
        }

        void top ( long value ) {
            myData.top = value;
        }

        long right () const {
            return (myData.right);
        }

        void right ( long value ) {
            myData.right = value;
        }

        long bottom () const {
            return (myData.bottom);
        }

        void bottom ( long value ) {
            myData.bottom = value;
        }

        long width () const {
            return (myData.right - myData.left);
        }

        long height () const {
            return (myData.bottom - myData.top);
        }

        Rectangle center ( const Rectangle& bounds ) const
        {
            const w32::gdi::Point middle = center();
            const w32::gdi::Point origin(
                middle.x() - bounds.width ()/2,
                middle.y() - bounds.height()/2);
            return (Rectangle(origin, bounds.span()));
        }
    };

} }

#endif /* _win32c_gdi_Rectangle_hpp__ */
