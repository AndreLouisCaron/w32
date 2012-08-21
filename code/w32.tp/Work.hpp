#ifndef _w32_tp_Work_hpp__
#define _w32_tp_Work_hpp__

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
#include <w32/Reference.hpp>
#include <w32.tp/Queue.hpp>

namespace w32 { namespace tp {

    class Hints;

    /*!
     * @ingroup w32-tp
     * @brief Registration for execution of a computation-bound task.
     */
    class Work
    {
        /* nested types. */
    public:
        template<void(*)(Hints&,void*)> struct function;
        template<typename T, void(T::*M)(Hints&)> struct method;

        typedef Reference<::PTP_WORK> Handle;

        typedef ::PTP_WORK_CALLBACK Callback;

        /* class methods. */
    private:
        static ::PTP_WORK setup
        ( ::PTP_CALLBACK_ENVIRON queue,
          ::PTP_WORK_CALLBACK callback, void * context );

    public:
        static Handle claim ( ::PTP_WORK object );
        static Handle proxy ( ::PTP_WORK object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Work ( const Handle& handle );

        Work ( Queue& queue, void * context, Callback entry )
            : myHandle(claim(setup(&queue.data(), entry, context)))
        {
        }

        template<void(*F)(Hints&,void*)>
        Work ( Queue& queue, function<F> function, void * context=0 )
            : myHandle(claim(setup(&queue.data(), function, context)))
        {
        }

        template<typename T, void(T::*M)(Hints&)>
        Work ( Queue& queue, T& object, method<T,M> method )
            : myHandle(claim(setup(&queue.data(), method, &object)))
        {
        }

        /* methods. */
    public:
        const Handle& handle () const;

        // Call to queue to the threadpool, may be called repeatedly.
        void submit ();
        void wait ( bool cancel_pending=false );
    };

    // compile-time binding of free function to callback function.
    template<void(*F)(Hints&,void*)>
    struct Work::function
    {
        operator Work::Callback () const
        {
            return (&work_callback);
        }

    private:
        static void __stdcall work_callback(
            ::PTP_CALLBACK_INSTANCE instance,
            void * context,
            ::PTP_WORK handle
            )
        {
            try {
                F(Hints(instance), context);
            }
            catch (const w32::Error& error)
            {
                std::cerr
                    << "Work handler: windows error " << error.code() << "."
                    << std::endl;
            }
            catch ( ... )
            {
                std::cerr
                    << "Exception raised from work handler."
                    << std::endl;
            }
        }
    };

    template<typename T, void(T::*M)(Hints&)>
    struct Work::method
    {
        operator Work::Callback () const
        {
            return (&work_callback);
        }

    private:
        static void __stdcall work_callback(
            ::PTP_CALLBACK_INSTANCE instance,
            void * context,
            ::PTP_WORK handle
            )
        {
            try {
                (static_cast<T*>(context)->*M)(Hints(instance));
            }
            catch (const w32::Error& error)
            {
                std::cerr
                    << "Work handler: windows error " << error.code() << "."
                    << std::endl;
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

#endif /* _w32_tp_Work_hpp__ */
