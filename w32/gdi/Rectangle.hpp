#ifndef _win32c_gdi_Rectangle_hpp__
#define _win32c_gdi_Rectangle_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"
#include <w32/gdi/Point.hpp>
#include <w32/gdi/Size.hpp>

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
