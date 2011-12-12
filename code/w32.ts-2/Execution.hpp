#ifndef _w32_ts2_Execution_hpp__
#define _w32_ts2_Execution_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

    class Executions;
    class State;

        /*!
         * @brief Communicates with a currently running task.
         */
    class Execution :
        public com::Wrapper< ::IRunningTask >
    {
        /* construction. */
    public:
            /*!
             * @brief Opens a specific task in a list of running tasks.
             *
             * @param index 1-based index to the desired task.
             */
        Execution ( const Executions& list, long index );

        /* methods. */
    public:
        bstring name () const;
        bstring path () const;
        bstring handler () const;
        bstring action () const;
        State state () const;
        void stop ();
        void refresh ();
    };

} }

#endif /* _w32_ts2_Execution_hpp__ */
