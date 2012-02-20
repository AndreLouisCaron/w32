#ifndef _w32_tp_Queue_hpp__
#define _w32_tp_Queue_hpp__

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
#include <w32/Error.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/Timespan.hpp>

namespace w32 { namespace tp {

    class Cleanup;
    class Hints;
    class Pool;

    /*!
     * @ingroup w32-tp
     * @brief Dispatch queue for a thread pool.
     */
    class Queue :
        private NotCopyable
    {
        /* nested types. */
    public:
        /*!
         * @brief Native representation of the callback queue.
         */
        typedef ::TP_CALLBACK_ENVIRON Data;

        /*!
         * @brief Native cleanupcallback signature.
         */
        typedef void(__stdcall*Cancel)(void*,void*);

        /*!
         * @brief Native signature for simple callback.
         */
        typedef void(__stdcall*Callback)(::PTP_CALLBACK_INSTANCE,void*);

        template<void(*)(Hints&,void*)> struct function;
        template<typename T, void(T::*M)(Hints&)> struct method;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        /*!
         * @brief Create a dispatch queue that uses @a pool's threads.
         */
        Queue ( Pool& pool );

        /*!
         * @brief Destroy the callback queue.
         *
         * @warning Invocation of any pending callbacks after the destructor
         *  has started execution results in undefined behavior.  Make sure
         *  all callback registrations are cancelled and all callback
         *  notifications are flushed before the queue is destroyed.
         */
        ~Queue ();

        /* methods. */
    public:
        /*!
         * @brief Obtain read-write access to the native representation.
         */
        Data& data ();

        /*!
         * @brief Obtain read-only access to the native representation.
         */
        const Data& data () const;

        /*!
         * @brief Registers a cleanup group for the callback queue.
         * @param cleanup The cleanup context.
         * @param cancel Cancellation function that is invoked once for each
         *  thread pool resource destroyed by the cleanup group.
         *
         * @warning Do @e not register a cleanup group if you intend to cleanup
         *  after the thread pool resources using other means (e.g. the @c Wait,
         *  @c Work, @c Timer and @c Transfer classes' destructors) because
         *  registration of a cleanup group destroys all affiliated thread pool
         *  resources automatically.  Registration of a cleanup group with
         *  managed thread pool resources results in undefined behavior.
         */
        void cleanup ( Cleanup& cleanup, Cancel cancel = 0 );

        /*!
         * @brief Schedule execution of a callback.
         * @param context Context pointer passed to @a function.
         * @param function Function that executes the work from a thread pool
         *  thread.
         */
        template<void(*F)(Hints&,void*)>
        void submit ( void * context, function<F> function )
        {
            const ::BOOL result = ::TrySubmitThreadpoolCallback
                (function, context, &data());
            if (result == FALSE)
            {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(TrySubmitThreadpoolCallback, error);
            }
        }

        /*!
         * @brief Schedule execution of a callback.
         * @param object Context object used to invoke @a method.
         * @param method Function that executes the work from a thread pool
         *  thread.
         */
        template<typename T, void(T::*M)(Hints&)>
        void submit ( T& object, method<T,M> method )
        {
            const ::BOOL result = ::TrySubmitThreadpoolCallback
                (method, &object, &data());
            if (result == FALSE)
            {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(TrySubmitThreadpoolCallback, error);
            }
        }
    };

    /*!
     * @brief Compile-time binding of free function to callback function.
     */
    template<void(*F)(Hints&,void*)>
    struct Queue::function
    {
        /*!
         * @brief Convert to a function pointer with the native signature.
         */
        operator Queue::Callback () const
        {
            return (&simple_callback);
        }

    private:
        static void __stdcall simple_callback
            ( ::PTP_CALLBACK_INSTANCE instance, void * context )
        {
            try {
                F(Hints(instance), context);
            }
            catch ( ... )
            {
                std::cerr
                    << "Exception raised from work handler."
                    << std::endl;
            }
        }
    };

    /*!
     * @brief Compile-time binding of member function to callback function.
     */
    template<typename T, void(T::*M)(Hints&)>
    struct Queue::method
    {
        /*!
         * @brief Convert to a function pointer with the native signature.
         */
        operator Queue::Callback () const
        {
            return (&simple_callback);
        }

    private:
        static void __stdcall simple_callback
            ( ::PTP_CALLBACK_INSTANCE instance, void * context )
        {
            try {
                (static_cast<T*>(context)->*M)(Hints(instance));
            }
            catch ( ... )
            {
                std::cerr
                    << "Exception raised from work handler."
                    << std::endl;
            }
        }
    };

} }

#endif /* _w32_tp_Queue_hpp__ */
