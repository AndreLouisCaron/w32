#ifndef _w32_mt_ConditionVariable_hpp__
#define _w32_mt_ConditionVariable_hpp__

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
#include <w32.mt/CriticalSection.hpp>
#include <w32.mt/ReadWriteLock.hpp>

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA

namespace w32 { namespace mt {

    /*!
     * @ingroup w32-mt
     * @brief Signal that some condition has been satisfied.
     *
     * In contrast with event objects, condition variables do not stay signaled.
     * Rather, they release any threads blocked on the condition at the moment
     * where the condition variable is signaled.  They support both the use case
     * of automatic reset events and manual reset events in that they can
     * release either a single waiting thread or all currently waiting threads.
     *
     * @see AutoResetEvent
     * @see ManualResetEvent
     */
    class ConditionVariable :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::CONDITION_VARIABLE Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        ConditionVariable ();
        ~ConditionVariable ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void signal ();
        void broadcast ();
        void sleep ( CriticalSection& lock );
        void sleep ( ReadWriteLock& lock, bool shared=false );
    };

} }

#endif

#endif /* _w32_mt_ConditionVariable_hpp__ */
