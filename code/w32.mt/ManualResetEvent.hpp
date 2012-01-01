#ifndef _w32_mt_ManualResetEvent_hpp__
#define _w32_mt_ManualResetEvent_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace mt {

    /*!
     * @ingroup w32-mt
     * @brief Signal that some condition has been satisfied.
     *
     * Contrarily to an automatic reset event, a manual reset event's state is
     * not cleared after a wait on the object is satisfied.  This means that a
     * variable number of threads may see the state of the event as signaled
     * before one of them resets the state.  As such, it is poorly suited to
     * producer-consumer scenarios and subject to race conditions when misused.
     *
     * @warning Manual reset events are one of the most misused synchronization
     *  primitives.  It is strongly recommended that you avoid them unless
     *  another entity requires a manual reset event or some existing software
     *  using one must be ported to this framework (hopefully as a first step
     *  to refactoring).
     *
     * @see ConditionVariable
     * @see AutoResetEvent
     */
    class ManualResetEvent :
        public Object
    {
        /* class methods. */
    public:
        static ManualResetEvent open ( const string& name );

        /* construction. */
    protected:
        explicit ManualResetEvent ( const Handle& handle );

    public:
        ManualResetEvent ();
        explicit ManualResetEvent ( const string& name );

        /* methods. */
    public:
        void set ();
        void reset ();

        void wait () const;
        bool wait ( const Timespan& timeout ) const;
        bool test () const;

        /* operators. */
    public:
        operator Waitable () const;
    };

} }

#endif /* _w32_mt_ManualResetEvent_hpp__ */
