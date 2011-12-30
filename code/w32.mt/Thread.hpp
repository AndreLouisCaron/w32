#ifndef _w32_mt_Thread_hpp__
#define _w32_mt_Thread_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/Timespan.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace mt {

        /*!
         * @brief Entity within a process that can be scheduled for execution.
         *
         * All threads of a process share its virtual address space and system
         * resources. In addition, each thread maintains exception handlers, a
         * scheduling priority, thread local storage, a unique thread
         * identifier, and a set of structures the system will use to save the
         * thread context until it is scheduled. The thread context includes
         * the thread's set of machine registers, the kernel stack, a thread
         * environment block, and a user stack in the address space of the
         * thread's process.
         *
         * Threads can also have their own security context, which can be used
         * for impersonating clients.
         */
    class Thread :
        public Object
    {
        /* nested types. */
    public:
        class Priority;

            /*!
             * @brief Integer value uniquely identifying a running thread.
             *
             * If you need to identify a thread through inter-process
             * communication, sending this value is more convenient than sending
             * the handle (which is not valid in the other process).
             */
        typedef dword Identifier;

            /*!
             * @brief Value returned by a thread to indicate status.
             */
        typedef dword Status;

            /*!
             * @brief Value that may be passed to induce context in the thread.
             * @see Function
             */
        typedef pointer Parameter;

            /*!
             * @brief Required function signature.
             * @see Parameter
             * @see Status
             * @see function
             * @see method
             */
        typedef Status(__stdcall*Function)(Parameter);

        template<dword(*)(void*)> struct function;
        template<typename T, dword(T::*)()> struct method;

        /* class methods. */
    public:
        static Thread current ();
        static Thread open ( Identifier identifier );

    private:
        static ::HANDLE allocate
            ( ::LPTHREAD_START_ROUTINE function, ::LPVOID context );

        /* construction. */
    public:
        explicit Thread ( const Handle& handle );
        explicit Thread ( Function function, Parameter parameter = 0 );

        template<dword(*F)(void*)>
        Thread ( function<F> function, void * context=0 )
        {
        }

        template<typename T, void(T::*M)()>
        Thread ( T& object, method<T,M> method )
        {
        }

        /* methods. */
    public:
            /*!
             * @brief Obtains the thread identifier.
             *
             * @return Theead identifier.
             * @see ExistingThread
             */
        Identifier identifier () const;

            /*!
             * @brief Obtains the thread' priority level.
             * @return The thread's priority.
             */
        Priority priority () const;

            /*!
             * @brief Changes the thread' priority level.
             * @param priority The thread's new priority level.
             */
        void priority ( const Priority& priority );

            /*!
             * @brief Suspends the target thread's execution (if running).
             *
             * @return Thread suspend count. If this 1, you have just
             *   pre-empted the thread and prevented it from being re-scheduled
             *   for execution.
             *
             * @warning This function is primarily destined for debuggers. In
             *   particular, <em>it is not intended for thread synchronization
             *   </em>. Suspending a thread that owns a synchronization resource
             *   is risking deadlock, @e even if that thread is well designed.
             */
        dword suspend ();

            /*!
             * @brief Attemps to wake up a thread that was @c suspend()ed.
             *
             * @note This function must be called if you created an initially
             *   suspended thread (useful trick for pre-allocating threads).
             *
             * @return Thread suspend count. When this is 0, the thread is no
             *   longer suspended and its execution is scheduled to resume.
             */
        dword resume ();

            /*!
             * @brief Kills the thread.
             *
             * This is a violent and brutal death and might cause chaos.
             *
             * @note Never use 259 as exit code because it is reserved. Using it
             *    may cause applications waiting on the process to run an
             *    infinite loop.
             *
             * @param status Exit code for the executing thread.
             */
        void terminate ( Status status = 0 );

            /*!
             * @brief Obtains the exit code for the thread.
             *
             * This status may have been set in a few different contexts: the
             * return value from the thread' entry point, the value set by the
             * thread when it called "ExitThread()", or the value set by the
             * caller to "TerminateThread()".
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
        Status status () const;

            /*!
             * @brief Checks if the thread is still alive and kicking.
             *
             * This is documented to work correctly, even though it actually
             * doesn't ask the system if the thread is alive (there are no
             * means to do so).
             *
             * @note Because 259 may technically be returned by a misbehaved
             *    thread, you should wait for the thread to complete to make
             *    sure the thread actually terminated. The wait functions
             *    are better suited for this.
             *
             * @return True if the thread's status is not 259.
             */
        bool alive () const;

        void join () const;
        bool join ( const Timespan& timeout ) const;

        /* operators. */
    public:
        operator Waitable () const;
    };

    // compile-time binding of free function to callback function.
    template<dword(*F)(void*)>
    struct Thread::function
    {
        operator ::LPTHREAD_START_ROUTINE () const
        {
            return (&entry_point);
        }

    private:
        static ::DWORD __stdcall entry_point ( ::LPVOID context )
        {
            return (F(context));
        }
    };

    template<typename T, dword(T::*M)()>
    struct Thread::method
    {
        operator ::LPTHREAD_START_ROUTINE () const
        {
            return (&entry_point);
        }

    private:
        static ::DWORD __stdcall entry_point ( ::LPVOID context )
        {
            return ((static_cast<T*>(context)->*M)());
        }
    };

        /*!
         * @brief Requests pause of execution for a fixed duration of time.
         *
         * The system cannot guarantee waking up \i exactly after the specified
         * amount of time. Make sure longer suspension is safe for your
         * application.
         */
    void sleep ( const Timespan& timespan );
    bool alertable ( const Timespan& timespan );

    class Sleep
    {
        w32::Timespan myTimespan;
    public:
        explicit Sleep ( const w32::Timespan& timespan )
            : myTimespan(timespan)
        {}

        void operator() () const
        {
            mt::sleep(myTimespan);
        }
    };

        /*!
         * @brief Hint to the scheduler for assining processor cycles.
         */
    class Thread::Priority
    {
        /* nested types. */
    public:
        typedef int Value;

        /* class data. */
    public:
        static const Priority idle ();
        static const Priority lowest ();
        static const Priority lower ();
        static const Priority normal ();
        static const Priority higher ();
        static const Priority highest ();
        static const Priority critical ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Priority ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

        /*!
         * @brief Prematurily ends the current thread's time slice.
         *
         * This mechanism is normally used for politeness: when executing a
         * potentially heavy task, the system may attribute extra processor
         * time for your thread. When that is the case, the system as a whole
         * may become less responsive. Use this to keep giving the illusion
         * of simultaneous execution.
         */
    void yield ();

        /*!
         * @brief Prematurily ends the current thread.
         *
         * The preferred means of ending a thread is returning from it's entry
         * point. In particular, this may cause resource leaks in your
         * application because C++ objects normally release resources in their
         * destructor and the stack is not unwound.
         */
    void exit ( uint status );

} }

#endif /* _w32_mt_Thread_hpp__ */
