#ifndef _w32_mt_Timer_hpp__
#define _w32_mt_Timer_hpp__

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
#include <w32/Object.hpp>
#include <w32/string.hpp>
#include <w32/Waitable.hpp>
#include <w32.fs/Time.hpp>

namespace w32 { namespace mt {

        /*!
         * @brief Timer used for synchronization.
         *
         * There are several principal modes of operation for waitable timers.
         * Any timer can be manual or automatic, single-use or periodic and can
         * be used solely as a waitable object or fire a callback when signaled.
         *
         * Once a timer's delai elapses, the timer is set to the signaled state:
         * subsequent wait(s) on the object will not block.
         *
         * Manual timers are used for signaling that some time delai elapsed.
         * They stay in the signaled state until a new expiry time is set. All
         * requests to wait for the timer will be granted.
         *
         * Automatic timers are used to schedule work by unblocking a single
         * waiting thread.  The timer stays in the single state until one wait
         * is satisfied and then returns to the non-signaled state.
         *
         * Single use timers need to be manually assigned a new expiry time
         * after time timer is signaled.  Periodic timers will be reset after
         * every expiry.
         *
         * Usual combinations are manual, single use timers and periodic,
         * automatic timers.  The former (manual, single-use) are of particular
         * interest to signal that some deadline has been reached.  The latter
         * (periodic, automatic) are of particular interest to schedule work on
         * a recurring basis.
         *
         * @todo Define semantics for scheduling a callback.  The MSDN is
         *  unclear on the subject and this requires experimentation.
         *
         * @note To set multiple timers and wait for whichever elapses first (or
         *  for all of them to elapse), you can use a @c Waitable::Set and store
         *  all related timers in the set.
         *
         * @ingroup mt
         */
    class Timer :
        public Object
    {
        /* class methods. */
    public:
            /*!
             * @brief Open a named timer.
             *
             * @see Timer(const string&)
             */
        static Timer open ( const string& name );

        /* construction. */
    public:
        explicit Timer ( const Handle& handle );

            /*!
             * @brief Create an unnamed timer.
             * @param manual @c false if a single thread should be release when
             *  the timer elapses, @c true if the timer should remain signaled
             *  until a new expiry time is set.
             */
        Timer ( bool manual=false );

            /*!
             * @brief Create a named timer.
             * @param name System-wide timer name, for inter-process
             *  communication.
             * @param manual @c false if a single thread should be release when
             *  the timer elapses, @c true if the timer should remain signaled
             *  until a new expiry time is set.
             *
             * @see open(const string&)
             */
        explicit Timer ( const string& name, bool manual=false );

        /* methods. */
    public:
            /*!
             * @brief Block the current thread until the timer elapses.
             */
        void wait () const;

            /*!
             * @brief Check if the timer elapsed (does not block).
             */
        bool elapsed () const;

            /*!
             * @brief Block the thread until the timer elapses.
             * @param timeout Maximum delai to wait for the timer.
             * @return @c true if the timer elapsed, @c false if the timeout
             *  delai was reached before the timer elapsed.
             */
        bool elapsed ( const Timespan& timeout ) const;

            /*!
             * @brief Invalidates the next expiry.
             *
             * This function prevents the next expiry time from being reached.
             * The timer will not pass from non-signaled to signaled state and
             * any asynchronous callbacks queued by this timer will not be run.
             *
             * If the timer is in manual mode and is already in the signaled
             * state, it will remain in that state.
             */
        void invalidate ();

            /*!
             * @brief Schedule the timer to be signaled.
             * @param expiry Time of next timer expiry.
             * @param period Non-zero value indicates period in milliseconds.
             *
             * If period is non-zero, then @a expiry denotes the first time the
             * timer will be signaled.  After that, each @a period milliseoncds,
             * the timer will become signaled again.
             */
        void set ( const fs::Time& expiry, long period=0 );

        /*!
         * @brief Schedule the timer to execute at regular intervals.
         */
        void periodic ( const Delta& period );

        /* operators. */
    public:
            /*!
             * @brief Expose the waitable interface.
             */
        operator Waitable () const;
    };

} }

#endif /* _w32_mt_Timer_hpp__ */
