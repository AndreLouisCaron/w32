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
 * @file w32/Delta.cpp
 * @brief Relative offsets for @c w32::Time instances.
 */

#include <w32/Delta.hpp>

namespace w32 {

    Delta Delta::microsecond ()
    {
        return (10);
    }

    Delta Delta::millisecond ()
    {
        return (1000*microsecond());
    }

    Delta Delta::second ()
    {
        return (1000*millisecond());
    }

    Delta Delta::minute ()
    {
        return (60*second());
    }

    Delta Delta::hour ()
    {
        return (60*minute());
    }

    Delta Delta::day ()
    {
        return (24*hour());
    }

    Delta Delta::year ()
    {
        return (365*day());
    }

    Delta Delta::leap_year ()
    {
        return (366*year());
    }

    Delta::Delta ()
        : myTicks(0)
    {
    }

    Delta::Delta ( qword ticks )
        : myTicks(ticks)
    {
    }

    qword Delta::ticks () const
    {
        return (myTicks);
    }

    dword Delta::milliseconds () const
    {
        return (static_cast<dword>(ticks() / millisecond().ticks()));
    }

    dword Delta::microseconds () const
    {
        return (static_cast<dword>(ticks() / microsecond().ticks()));
    }

    dword Delta::seconds () const
    {
        return (static_cast<dword>(ticks() / second().ticks()));
    }

    Delta& Delta::operator*= ( int rhs )
    {
        myTicks *= rhs; return (*this);
    }

    Delta& Delta::operator*= ( double rhs )
    {
        myTicks = static_cast<qword>(double(myTicks)*rhs); return (*this);
    }

    Delta& Delta::operator/= ( int rhs )
    {
        myTicks /= rhs; return (*this);
    }

    Delta& Delta::operator+= ( const Delta& rhs )
    {
        myTicks += rhs.myTicks; return (*this);
    }

    Delta& Delta::operator-= ( const Delta& rhs )
    {
        myTicks -= rhs.myTicks; return (*this);
    }

    Delta operator+ ( const Delta& lhs, const Delta& rhs )
    {
        Delta result = lhs; result += rhs; return (result);
    }

    Delta operator- ( const Delta& lhs, const Delta& rhs )
    {
        Delta result = lhs; result -= rhs; return (result);
    }

    Delta operator* ( const Delta& lhs, int rhs )
    {
        Delta result = lhs; result *= rhs; return (result);
    }

    Delta operator* ( int lhs, const Delta& rhs )
    {
        Delta result = rhs; result *= lhs; return (result);
    }

    Delta operator* ( const Delta& lhs, double rhs )
    {
        Delta result = lhs; result *= rhs; return (result);
    }

    Delta operator* ( double lhs, const Delta& rhs )
    {
        Delta result = rhs; result *= lhs; return (result);
    }

    Delta operator/ ( const Delta& lhs, int rhs )
    {
        Delta result = lhs; result /= rhs; return (result);
    }

    double operator/ ( const Delta& lhs, const Delta& rhs )
    {
        return (double(lhs.ticks()) / double(rhs.ticks()));
    }

    bool operator> ( const Delta& lhs, const Delta& rhs )
    {
        return (lhs.ticks() > rhs.ticks());
    }

    bool operator< ( const Delta& lhs, const Delta& rhs )
    {
        return (lhs.ticks() < rhs.ticks());
    }

    bool operator<= ( const Delta& lhs, const Delta& rhs )
    {
        return (lhs.ticks() <= rhs.ticks());
    }

    bool operator>= ( const Delta& lhs, const Delta& rhs )
    {
        return (lhs.ticks() >= rhs.ticks());
    }

}
