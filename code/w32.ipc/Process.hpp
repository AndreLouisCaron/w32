#ifndef _w32_ipc_Process_hpp__
#define _w32_ipc_Process_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/Object.hpp>
#include <w32/Waitable.hpp>
#include <w32.mt/Thread.hpp>

namespace w32 { namespace ipc {

        /*!
         * @brief Program execution context.
         *
         * Each process provides the resources needed to execute a program. A
         * process has a virtual address space, executable code, open handles to
         * system objects, a security context, a unique process identifier,
         * environment variables, a priority class, minimum and maximum working
         * set sizes, and at least one thread of execution.
         */
    class Process :
        public Object
    {
        /* nested types. */
    public:
            /*!
             * @brief Integer value uniquely identifying a running process.
             *
             * If you need to identify a process through inter-process
             * communication, sending this value is more convenient than sending
             * the handle (which is not valid in the other process).
             */
        typedef dword Identifier;

        class Priority;

        /* class methods. */
    public:
        static Process current ();

        /* construction. */
    public:
        explicit Process ( const Handle& handle );
        explicit Process ( Identifier identifier );
        explicit Process ( const string& executable, bool inherit=false );

        /* methods. */
    public:
            /*!
             * @brief Obtains the process identifier.
             *
             * @return Process identifier.
             * @see ExistingProcess
             */
        Identifier identifier () const;

            /*!
             * @brief Obtains the process' priority level.
             * @return The process's priority.
             */
        Priority priority () const;

            /*!
             * @brief Changes the process' priority level.
             * @param priority The prcess's new priority level.
             */
        void priority ( const Priority& priority );

            /*!
             * @brief Indicates if priority should be boosted when waking up.
             *
             * When a thread is running in one of the dynamic priority classes,
             * the system temporarily boosts the thread's priority when it is
             * taken out of a wait state.
             *
             * @note By default, this is enabled for new processes.
             * @return True if boosting is enabled.
             */
        bool boosted () const;

            /*!
             * @brief Indicates if priority should be boosted when waking up.
             *
             * When a thread is running in one of the dynamic priority classes,
             * the system temporarily boosts the thread's priority when it is
             * taken out of a wait state.
             *
             * @note By default, this is enabled for new processes.
             */
        void boosted ( bool boost );

            /*!
             * @brief Obtains the number of system object handles used.
             *
             * As processes are inherently in concurrent execution, this count
             * is only useful as an estimate: chances are it changes multiple
             * times per second.
             *
             * @return The number of handles.
             */
        dword handles () const;

            /*!
             * @brief Kills the process.
             *
             * This is a violent and brutal death and might cause chaos.
             *
             * @note Never use 259 as exit code because it is reserved. Using it
             *    may cause applications waiting on the process to run an
             *    infinite loop.
             *
             * @param status Exit code for the executing program.
             */
        void terminate ( uint status = 0 );

            /*!
             * @brief Obtains the exit code for the process.
             *
             * This status may have been set in a few different contexts: the
             * return value from the process' entry point, the value set by the
             * process when it called "exit()" or "ExitProcess()", or the value
             * set by the process that terminated it.
             *
             * Note that this function never blocks, even if the process is
             * still alive. If so, a special code (259) is returned.
             *
             * @note Because 259 may technically be returned by a misbehaved
             *    process, you should wait for the thread to complete and only
             *    then request the status code.
             *
             * @return Status, or 259 (still alive).
             */
        dword status () const;

            /*!
             * @brief Checks if the process is still alive and kicking.
             *
             * This is documented to work correctly, even though it actually
             * doesn't ask the system if the process is alive (there are no
             * means to do so).
             *
             * @note Because 259 may technically be returned by a misbehaved
             *    process, you should wait for the process to complete to make
             *    sure the process actually terminated. The wait functions
             *    are better suited for this.
             *
             * @return True if the process' status is not 259.
             */
        bool alive () const;

            /*!
             * @brief Waits until the process ends.
             *
             * Unless you control the given process, calling this method is
             * dangerous and not recommended because it can result in your
             * program waiting forever.
             */
        void join () const;

            /*!
             * @brief Waits until the process ends or the timeout elapses.
             * @param timeout Maximum period of time to wait for the process.
             * @return False if the timeout elapsed.
             */
        bool join ( const Timespan& timeout ) const;

            /*!
             * @brief Checks if the process is already completed (doesn't wait).
             * @return True if the process has completed.
             */
        bool test () const;

            /*!
             * @brief Allocate memory in target process.
             * @param size Amount of memory to allocate (in bytes).
             * @return Virtual address in remote process space.
             *
             * @see release()
             * @see get()
             * @see put()
             */
        pointer acquire ( size_t size );

            /*!
             * @brief Free memory in target process.
             * @param base Virtual address in remote process space.
             *
             * @see acquire()
             */
        void release ( pointer base );

            /*!
             * @brief Copy memory from target process to current process.
             * @param base Virtual address in remote process space.
             * @param data Virtual address in current process space.
             * @param size Amount of memory to copy (in bytes).
             * @return Number of bytes copied.
             */
        size_t get ( pointer base, void * data, size_t size ) const;

            /*!
             * @brief Copy memory from current process to target process.
             * @param base Virtual address in remote process space.
             * @param data Virtual address in current process space.
             * @param size Amount of memory to copy (in bytes).
             * @return Number of bytes copied.
             */
        size_t put ( pointer base, const void * data, size_t size );

            /*!
             * @brief Start thread in target process.
             * @param code Virtual address of function in target process space.
             * @param base Virtual address of context in target process space.
             * @return Thread instance for control and synchronization.
             *
             * @see acquire()
             * @see symbol()
             */
        mt::Thread call ( pointer code, pointer base );

            /*!
             * @brief Find exported symbol address in target process.
             * @param base Module virtual base address in target process.
             * @param name Symbol name.
             *
             * @see Modules
             * @see run()
             */
        pointer symbol ( pointer base, const astring& name );

        /* operators. */
    public:
        operator Waitable () const;
    };

    /*!
     * @brief Hint to the scheduler for assining processor cycles.
     */
     class Process::Priority
     {
         /* nested types. */
     public:
         typedef dword Value;

         /* class data. */
     public:
         static const Priority higher ();
         static const Priority lower ();
         static const Priority high ();
         static const Priority normal ();
         static const Priority idle ();
         static const Priority realtime ();

         /* data. */
     private:
         Value myValue;

         /* construction. */
     private:
             // For internal use only.
         Priority ( Value value );

         /* class methods. */
     public:
         static Priority of ( const Process& process );

         /* methods. */
     public:
         Value value () const;
     };

        /*!
         * @brief Terminates the current process.
         *
         * This is a violent and brutal death and might cause chaos.
         *
         * @note Never use 259 as exit code because it is reserved. Using it
         *    may cause applications waiting on the process to run an
         *    infinite loop.
         *
         * @param status Exit code for the executing program.
         */
    void exit ( uint code );

} }

#endif /* _w32_ipc_Process_hpp__ */
