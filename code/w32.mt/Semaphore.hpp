#ifndef _w32_mt_Semaphore_hpp__
#define _w32_mt_Semaphore_hpp__

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
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace mt {

    /*!
     * @ingroup w32-mt
     * @brief Thread-safe counter, often used in producer-consumer scenarios.
     * @see Mutex
     */
    class Semaphore :
        public Object
    {
        /* nested types. */
    public:
            /*!
             * @brief Scoped ownership.
             */
        class Lock :
            private NotCopyable
        {
            /* data. */
        private:
            Semaphore& mySemaphore;

            /* construction. */
        public:
            explicit Lock ( Semaphore& mutex );
            Lock ( Semaphore& mutex, const Timespan& timeout );
            ~Lock ();
        };

        /* construction. */
    public:
        Semaphore ( long initial, long maximum );

        /* methods. */
    public:
            /*!
             * @brief Waits until a share of the semaphore lock is available.
             */
        void acquire ();

            /*!
             * @brief Waits until a share of the semaphore lock is available, or
             *    until the timeout expires.
             *
             * @return False if the timeout expired.
             */
        bool acquire ( const Timespan& timeout );

            /*!
             * @brief Makes the lock available for another thread.
             * @param count Number of shares to release.
             * @return Number of available shares, after the release operation.
             */
        long release ( long count = 1 );

        /* operators. */
    public:
        operator Waitable () const;
    };

} }

#endif /* _w32_mt_Semaphore_hpp__ */
