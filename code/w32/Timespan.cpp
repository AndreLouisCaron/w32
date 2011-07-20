// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Timespan.hpp>

namespace w32 {

    const Timespan::Unit Timespan::Unit::native ()
    {
        return (1);
    }

    const Timespan::Unit Timespan::Unit::millisecond ()
    {
        return (native());
    }

    const Timespan::Unit Timespan::Unit::second ()
    {
        return (Value(1000) * millisecond().ticks());
    }

    const Timespan::Unit Timespan::Unit::minute ()
    {
        return (Value(60) * second().ticks());
    }

    const Timespan::Unit Timespan::Unit::hour ()
    {
        return (Value(60) * minute().ticks());
    }

    const Timespan::Unit Timespan::Unit::day ()
    {
        return (Value(24) * hour().ticks());
    }

    const Timespan::Unit Timespan::Unit::week()
    {
        return (Value(7) * day().ticks());
    }

    Timespan::Unit::Unit ( Value ticks )
        : myTicks(ticks)
    {
    }

    Timespan::Value Timespan::Unit::ticks () const
    {
        return (myTicks);
    }

    Timespan::Unit& Timespan::Unit::operator*= ( Value factor )
    {
        myTicks *= factor;
        return (*this);
    }

    Timespan::Unit& Timespan::Unit::operator*= ( double factor )
    {
        myTicks = static_cast<Value>(static_cast<double>(myTicks) * factor);
        return (*this);
    }

    const Timespan Timespan::infinite ()
    {
        return (Timespan(INFINITE));
    }

    Timespan::Timespan ()
        : myTicks(0)
    {
    }

    Timespan::Timespan ( Value ticks )
        : myTicks(ticks)
    {
    }

    Timespan::Timespan ( Value ticks, const Unit& unit )
        : myTicks(ticks * unit.ticks())
    {
    }

    bool Timespan::empty () const
    {
        return (myTicks == 0);
    }

    Timespan::Value Timespan::ticks () const
    {
        return (myTicks);
    }

    double Timespan::get ( const Unit& unit ) const
    {
        return (static_cast<double>(ticks()) /
                static_cast<double>(unit.ticks()));
    }

}
