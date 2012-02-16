#ifndef _w32_mt_Mutex_hpp__
#define _w32_mt_Mutex_hpp__

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
#include <w32/string.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace mt {

    /*!
     * @ingroup w32-mt
     * @brief Mutual exclusion lock with support for sharing between processes.
     * @see CriticalSection
     */
    class Mutex :
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
            Mutex& myMutex;

            /* construction. */
        public:
            explicit Lock ( Mutex& mutex );
            Lock ( Mutex& mutex, const Timespan& timeout );
            ~Lock ();
        };

        /* class methods. */
    public:
        static Mutex open ( const string& name );

        /* construction. */
    protected:
        explicit Mutex ( const Handle& handle );

    public:
        Mutex ();
        explicit Mutex ( const string& name );

        /* methods. */
    public:
            /*!
             * @brief Waits until the mutex lock is available.
             */
        void acquire ();

            /*!
             * @brief Waits until the mutex lock is available, or until the
             *    timeout expires.
             *
             * @return False if the timeout expired.
             */
        bool acquire ( const Timespan& timeout );

            /*!
             * @brief Makes the lock available for another thread.
             */
        void release ();

        /* operators. */
    public:
        operator Waitable () const;
    };

} }

#endif /* _w32_mt_Mutex_hpp__ */
