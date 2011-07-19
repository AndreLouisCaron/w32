#ifndef _w32_gdi_ProgressBar_hpp__
#define _w32_gdi_ProgressBar_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

    class Rectangle;

        /*!
         * @brief Control used to display status messages.
         */
    class ProgressBar :
        public Control
    {
        /* nested types. */
    public:
        class Range;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated progress bar.
             *
             * @see claim()
             * @see proxy()
             */
        explicit ProgressBar ( const Handle& handle );

            /*!
             * @brief Creates a new progress bar on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        ProgressBar ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief Changes the current position by a relative offset.
             */
        int displace ( int delta );

            /*!
             * @brief Increments the position by one step.
             * @return The previous range.
             * @see step()
             */
        int next ();

            /*!
             * @brief Changes the current position to an absolute value.
             * @return The previous absolute position.
             */
        int position ( int value );

            /*!
             * @brief Obtains the current absolute position in the range.
             */
        int position () const;

            /*!
             * @brief Changes the range of acceptable values (default=[0,100]).
             * @return The previous range.
             * @see Range
             */
        Range range ( const Range& value );

            /*!
             * @brief Changes the delta value of a single step.
             * @see next()
             */
        int step ( int delta );
    };

    class ProgressBar::Range
    {
        /* data. */
    private:
        ::PBRANGE myData;

        /* construction. */
    public:
        Range ();
        Range ( int low, int high );
        Range ( const ::PBRANGE& data );

        /* methods. */
    public:
        ::PBRANGE& get ();
        const ::PBRANGE& get () const;
        int low () const;
        int high () const;
        void low ( int value );
        void high ( int value );
    };

} }

#endif /* _w32_gdi_ProgressBar_hpp__ */
