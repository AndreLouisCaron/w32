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

    class Timespan
    {
        /* nested types. */
    public:
        typedef dword Value;

        class Unit;

        /* class data. */
    public:
        static const Timespan infinite ();

        /* data. */
    private:
        Value myTicks;

        /* construction. */
    public:
        Timespan ();
        explicit Timespan ( Value ticks );
        Timespan ( Value ticks, const Unit& unit );

        /* methods. */
    public:
        bool empty () const;

        Value ticks () const;

        double get () const;
        double get ( const Unit& unit ) const;
    };

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
        Unit ( Value ticks );

        /* methods. */
    public:
            /*!
            * @brief Multiple of the native resolution.
            */
        Value ticks () const;

        /* operators. */
    public:
        Unit& operator*= ( Value factor );
        Unit& operator*= ( double factor );
    };

}

#endif /* _w32_Timespan_hpp__ */
