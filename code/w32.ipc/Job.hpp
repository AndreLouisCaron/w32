#ifndef _w32_ipc_Job_hpp__
#define _w32_ipc_Job_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/Object.hpp>
#include <w32.ipc/Process.hpp>

namespace w32 { namespace ipc {

        /*!
         * @brief Group of processes.
         *
         * This is a tool for management of multiple sub-processes and is ideal
         * for a control process. Operations performed on the job object are
         * propagated to all processes associated with the job.
         *
         * By default, all child processes of a process in a job are also
         * assigned to the job. It is possible to override this behaviour.
         */
    class Job :
        public Object
    {
        /* class methods. */
    public:
        static Job open ( const string& name );

        /* construction. */
    protected:
        explicit Job ( const Handle& handle );

    public:
        Job ();
        explicit Job ( const string& name );

        /* methods. */
    public:
            /*!
             * @brief Assigns a process to the process group.
             *
             * A process may be only assigned to a single job. This binding
             * lasts for the lifetime of the process and cannot be broken.
             */
        void add ( Process& process );

            /*!
             * @brief Checks if the process was assigned to the process group.
             *
             * @param process Process who'se status we're interested in.
             * @return True if the process has been assigned to the job.
             */
        bool contains ( const Process& process );

            /*!
             * @brief Kills all processes in the process group.
             *
             * This is a violent and brutal death and might cause chaos.
             *
             * @param status Exit code to propagate to all those in the group.
             */
        void terminate ( uint status );
    };

} }

#endif /* _w32_ipc_Job_hpp__ */
