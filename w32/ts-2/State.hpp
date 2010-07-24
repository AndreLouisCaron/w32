#ifndef _w32_ts2_State_hpp__
#define _w32_ts2_State_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

    class Execution;
    class Registration;

    class W32_TS2_EXPORT State
    {
        /* nested types. */
    public:
        typedef ::TASK_STATE Value;

        /* class data. */
    public:
        static const State unknown ();
        static const State disabled ();
        static const State queued ();
        static const State ready ();
        static const State running ();

        /* class methods. */
    public:
        static State of ( const Execution& task );
        static State of ( const Registration& task );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        State ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;

        bool operator== ( const State& other ) const;
        bool operator!= ( const State& other ) const;
    };

} }

#endif /* _w32_ts2_State_hpp__ */

