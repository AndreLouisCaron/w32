#ifndef _w32_Timespan_hpp__
#define _w32_Timespan_hpp__

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
#include <w32/types.hpp>

namespace w32 {

    /*!
     * @brief Encodes a length of time in system counter "ticks".
     */
    class Timespan
    {
        /* nested types. */
    public:
        /*!
         * @brief Unsigned integer multiple of the quantum unit.
         *
         * Native units are the lowest possible resolution the system
         * recognizes.  It is a common denominator: any timespan can be
         * expressed using an integer multiple of this unit.
         *
         * For backward compatibility reasons, this is a number of
         * milliseconds, regardless of the actual quantum your hardware may
         * provide.
         */
        typedef dword Value;

        class Unit;

        /* class data. */
    public:
        /*!
         * @brief Special value representing an infinite amount of time.
         */
        static const Timespan infinite ();

        /* data. */
    private:
        Value myTicks;

        /* construction. */
    public:
        /*!
         * @brief Builds a null (empty) timespan (0 in any kind of units).
         */
        Timespan ();

        /*!
         * @brief Build a timespan as a multiple of the quantum unit.
         * @param ticks Number of ticks the timespan should represent.
         */
        explicit Timespan ( Value ticks );

        /*!
         * @brief Build a timespan as a multiple of a specific unit.
         * @param ticks Number of ticks the timespan should represent.
         */
        Timespan ( Value ticks, const Unit& unit );

        /* methods. */
    public:
        /*!
         * @return @c true if the timespan equals 0 ticks, else @c false.
         */
        bool empty () const;

        /*!
         * @brief Integer multiple of ticks the timespan represents.
         */
        Value ticks () const;

        /*!
         * @brief Express the timespan in multiples of the quantum unit.
         */
        double get () const;

        /*!
         * @brief Express the timespan in multiples of @a unit.
         *
         * This method returns a floating-point value because the timespan may
         * not be an integer of multiple @c unit (@c unit might be longer
         * than @c *this in duration).
         */
        double get ( const Unit& unit ) const;
    };

    /*!
     * @brief Enumeration of common time span reference units.
     */
    class Timespan::Unit
    {
        /* class data. */
    public:
        static const Unit native ();
        static const Unit millisecond ();
        static const Unit second ();
        static const Unit minute ();
        static const Unit hour ();
        static const Unit day ();
        static const Unit week ();

        /* data. */
    private:
        Value myTicks;

        /* construction. */
    private:
        // For internal use only.
        Unit ( Value ticks );

        /* methods. */
    public:
        /*!
         * @brief Multiple of the native resolution.
         */
        Value ticks () const;

        /* operators. */
    public:
        /*!
         * @brief Obtain a multiple of the selected unit.
         */
        Unit& operator*= ( Value factor );

        /*!
         * @brief Obtain a multiple of the selected unit.
         */
        Unit& operator*= ( double factor );
    };

}

#endif /* _w32_Timespan_hpp__ */
