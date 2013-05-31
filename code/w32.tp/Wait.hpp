#ifndef _w32_tp_Wait_hpp__
#define _w32_tp_Wait_hpp__

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
     * @brief Registration for notification after a wait condition is satisfied.
     */
    class Wait
    {
        /* nested types. */
    public:
        template<void(*F)(Hints&,void*)> struct function;
        template<typename T, void(T::*M)(Hints&)> struct method;

        typedef Reference<::PTP_WAIT> Handle;

        typedef ::PTP_WAIT_CALLBACK Callback;

        /* class methods. */
    private:
        static ::PTP_WAIT setup
        ( ::PTP_CALLBACK_ENVIRON queue,
          ::PTP_WAIT_CALLBACK function, void * context );

    public:
        static Handle claim ( ::PTP_WAIT object );
        static Handle proxy ( ::PTP_WAIT object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Wait ( const Handle& handle );

        Wait ( Queue& queue, void * context, Callback entry )
            : myHandle(claim(setup(&queue.data(), entry, context)))
        {
        }

        template<void(*F)(Hints&,void*)>
        Wait ( Queue& queue, function<F> function, void * context=0 )
            : myHandle(claim(setup(&queue.data(), function, context)))
        {
        }

        template<typename T, void(T::*M)(Hints&)>
        Wait ( Queue& queue, T& object, method<T,M> method )
            : myHandle(claim(setup(&queue.data(), method, &object)))
        {
        }

        /* methods. */
    public:
        const Handle& handle () const;

        void watch ( ::HANDLE waitable );
        void clear ();

        void wait ( bool cancel_pending=false );
    };

    // compile-time binding of free function to callback function.
    template<void(*F)(Hints&,void*)>
    struct Wait::function
    {
        operator ::PTP_WAIT_CALLBACK () const
        {
            return (&wait_callback);
        }

    private:
       static void __stdcall wait_callback(
            ::PTP_CALLBACK_INSTANCE instance,
            void * context,
            ::PTP_WAIT handle,
            ::TP_WAIT_RESULT result
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
    struct Wait::method
    {
        operator ::PTP_WAIT_CALLBACK () const
        {
            return (&wait_callback);
        }

    private:
        static void __stdcall wait_callback(
            ::PTP_CALLBACK_INSTANCE instance,
            void * context,
            ::PTP_WAIT handle,
            ::TP_WAIT_RESULT result
            )
        {
            try {
                (static_cast<T*>(context)->*M)(Hints(instance));
            }
            catch (const w32::Error& error)
            {
                std::cerr
                    << "Wait handler: windows error " << error.code() << "."
                    << std::endl;
            }
            catch ( ... )
            {
                std::cerr
                    << "Exception raised from wait handler."
                    << std::endl;
            }
        }
    };

} }

#endif /* _w32_tp_Wait_hpp__ */
