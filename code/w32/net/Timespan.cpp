// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/Timespan.hpp>

namespace w32 { namespace net {

    Timespan::Timespan ()
    {
        ::ZeroMemory(&myValue, sizeof(myValue));
    }

    Timespan::Timespan ( const Value& value )
        : myValue(value)
    {
    }

    Timespan::Timespan ( long seconds, long microseconds )
    {
        myValue.tv_sec = seconds;
        myValue.tv_usec = microseconds;
    }

    Timespan::Value& Timespan::value ()
    {
        return (myValue);
    }

    const Timespan::Value& Timespan::value () const
    {
        return (myValue);
    }

    long Timespan::seconds () const
    {
        return (myValue.tv_sec);
    }

    void Timespan::seconds ( long value )
    {
        myValue.tv_sec = value;
    }

    long Timespan::microseconds () const
    {
        return (myValue.tv_usec);
    }

    void Timespan::microseconds ( long value )
    {
        myValue.tv_usec = value;
    }

} }
