#ifndef _w32_gdi_ProgressBar_hpp__
#define _w32_gdi_ProgressBar_hpp__

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
