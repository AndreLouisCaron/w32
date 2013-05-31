#ifndef _w32_Delta_hpp__
#define _w32_Delta_hpp__

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

/*!
 * @file w32/Delta.hpp
 * @brief Relative offsets for @c w32::Time instances.
 */

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 {

    //! @addtogroup w32
    //! @{

    /*!
     * @brief Relative offset for @c Time instances.
     *
     * The native resolution for time deltas is a 100 nanoseconds (1/10 of a
     * microsecond).  Keep in mind that not all functions that accept a @c Time
     * instance support such a fine-grained resolution.  Many operate at a
     * resolution larger than 1 millisecond.
     *
     * @see Time
     */
    class Delta
    {
        /* class methods. */
    public:
        /*!
         * @brief One microsecond (us) delta.
         */
        static Delta microsecond ();

        /*!
         * @brief One millisecond (ms) delta.
         */
        static Delta millisecond ();

        /*!
         * @brief One second (s) delta.
         */
        static Delta second ();

        /*!
         * @brief One minute (m) delta.
         */
        static Delta minute ();

        /*!
         * @brief One hour (h) delta.
         */
        static Delta hour ();

        /*!
         * @brief One day (d) delta.
         */
        static Delta day ();

        /*!
         * @brief One year (d) delta (365 days).
         * @see leap_year()
         */
        static Delta year ();

        /*!
         * @brief One leap year (d) delta (366 days).
         * @see year()
         */
        static Delta leap_year ();

        /* data. */
    private:
        // Number of slices of 100 nanoseconds.
        qword myTicks;

        /* construction. */
    public:
        /*!
         * @brief Create a null delta, represents "no offset".
         */
        Delta ();

    private:
        // For internal use only.
        Delta ( qword ticks );

        /* methods. */
    public:
        /*!
         * @brief Get the delta as an integer multiple of the native resolution.
         *
         * @note The native resolution is 100 nanoseconds (1/10 us).
         */
        qword ticks () const;

        dword microseconds () const;
        dword milliseconds () const;
        dword seconds () const;

        /* operators. */
    public:
        /*!
         * @brief Compute an integer multiple of the delta.
         */
        Delta& operator*= ( int rhs );

        /*!
         * @brief Compute a multiple of the delta.
         */
        Delta& operator*= ( double rhs );

        /*!
         * @brief Compute an integer fraction of the delta.
         */
        Delta& operator/= ( int rhs );

        /*!
         * @brief Increase the time delta.
         */
        Delta& operator+= ( const Delta& rhs );

        /*!
         * @brief Decrease the time delta.
         */
        Delta& operator-= ( const Delta& rhs );
    };

    /*!
     * @brief Increase the time delta.
     */
    Delta operator+ ( const Delta& lhs, const Delta& rhs );

    /*!
     * @brief Decrease the time delta.
     */
    Delta operator- ( const Delta& lhs, const Delta& rhs );

    /*!
     * @brief Compute an integer multiple of a delta.
     */
    Delta operator* ( const Delta& lhs, int rhs );

    /*!
     * @brief Compute an integer multiple of a delta.
     */
    Delta operator* ( int lhs, const Delta& rhs );

    /*!
     * @brief Compute a multiple of a delta.
     */
    Delta operator* ( const Delta& lhs, double rhs );

    /*!
     * @brief Compute a multiple of a delta.
     */
    Delta operator* ( double lhs, const Delta& rhs );

    /*!
     * @brief Compute an integer fraction of a delta.
     */
    Delta operator/ ( const Delta& lhs, int rhs );

    /*!
     * @brief Compute the relative size of two delta.
     */
    double operator/ ( const Delta& lhs, const Delta& rhs );

    bool operator> ( const Delta& lhs, const Delta& rhs );
    bool operator< ( const Delta& lhs, const Delta& rhs );
    bool operator<= ( const Delta& lhs, const Delta& rhs );
    bool operator>= ( const Delta& lhs, const Delta& rhs );

    //! @}

}

#endif /* _w32_Delta_hpp__ */
