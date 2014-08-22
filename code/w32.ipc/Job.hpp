#ifndef _w32_ipc_Job_hpp__
#define _w32_ipc_Job_hpp__

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

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/Object.hpp>
#include <w32.ipc/Process.hpp>

namespace w32 { namespace ipc {

    /*!
     * @ingroup w32-ipc
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

        void join () const;
        bool join (w32::Timespan timeout) const;

        /* operators. */
    public:
        operator Waitable () const;
    };

} }

#endif /* _w32_ipc_Job_hpp__ */
