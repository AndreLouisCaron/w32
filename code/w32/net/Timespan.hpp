#ifndef _w32_net_Timespan_hpp__
#define _w32_net_Timespan_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/net/Context.hpp>
#include <w32/net/Socket.hpp>

namespace w32 { namespace net {

    class Timespan
    {
        /* nested types. */
    public:
        typedef ::TIMEVAL Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Timespan ();
        Timespan ( const Value& value );
        Timespan ( long seconds, long microseconds = 0 );

        /* methods. */
    public:
        Value& value ();
        const Value& value () const;

        long seconds () const;
        void seconds ( long value );
        long microseconds () const;
        void microseconds ( long value );
    };

} }

#endif /*  _w32_net_Timespan_hpp__ */
