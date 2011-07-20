#ifndef _w32_Timespan_hpp__
#define _w32_Timespan_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
