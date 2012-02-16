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
