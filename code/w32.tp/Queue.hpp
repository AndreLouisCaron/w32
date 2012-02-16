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
     * @brief Dispatch queue for a group of threads.
     */
    class Queue :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::TP_CALLBACK_ENVIRON Data;

        typedef void (__stdcall*Cancel)(void*,void*);

        template<void(*)(Hints&,void*)> struct function;
        template<typename T, void(T::*M)(Hints&)> struct method;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Queue ( Pool& pool );
        ~Queue ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void cleanup ( Cleanup& cleanup, Cancel cancel = 0 );

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

    // compile-time binding of free function to callback function.
    template<void(*F)(Hints&,void*)>
    struct Queue::function
    {
        operator ::PTP_SIMPLE_CALLBACK () const
        {
            return (&simple_callback);
        }

    private:
        static void __stdcall simple_callback
            ( ::PTP_CALLBACK_INSTANCE instance, void * context )
        {
            F(Hints(instance), context);
        }
    };

    // compile-time binding of object method to callback function.
    template<typename T, void(T::*M)(Hints&)>
    struct Queue::method
    {
        operator ::PTP_SIMPLE_CALLBACK () const
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
