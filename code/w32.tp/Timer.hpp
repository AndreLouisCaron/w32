#ifndef _w32_tp_Timer_hpp__
#define _w32_tp_Timer_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32.tp/Queue.hpp>

namespace w32 { namespace tp {

    class Hints;

    // Use for general timer facilities (timeouts on non-I/O operations).
    class Timer
    {
        /* nested types. */
    public:
        template<void(*F)(Hints&,void*)> struct function;
        template<typename T, void(T::*M)(Hints&)> struct method;

        typedef Reference<::PTP_TIMER> Handle;

        /* class methods. */
    private:
        static ::PTP_TIMER setup
        ( ::PTP_CALLBACK_ENVIRON queue,
          ::PTP_TIMER_CALLBACK callback, void * context );

    public:
        static Handle claim ( ::PTP_TIMER object );
        static Handle proxy ( ::PTP_TIMER object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public: 
        explicit Timer ( const Handle& handle );

        template<void(*F)(Hints&,void*)>
        Timer ( Queue& queue, function<F> function, void * context=0 )
            : myHandle(claim(setup(&queue.data(), function, context)))
        {
        }

        template<typename T, void(T::*M)(Hints&)>
        Timer ( Queue& queue, T& object, method<T,M> method )
            : myHandle(claim(setup(&queue.data(), method, &object)))
        {
        }

        /* methods. */
    public:
        const Handle& handle () const;

        void start ( ::DWORD delai, ::DWORD period=0 );
        void cancel ();

        void wait ( bool cancel_pending=false );
    };

    // compile-time binding of free function to callback function.
    template<void(*F)(Hints&,void*)>
    struct Timer::function
    {
        operator ::PTP_TIMER_CALLBACK () const
        {
            return (&timer_callback);
        }

    private:
        static void __stdcall timer_callback(
            ::PTP_CALLBACK_INSTANCE instance,
            void * context,
            ::PTP_TIMER handle
            )
        {
            F(Hints(instance), context);
        }
    };

    template<typename T, void(T::*M)(Hints&)>
    struct Timer::method
    {
        operator ::PTP_TIMER_CALLBACK () const
        {
            return (&timer_callback);
        }

    private:
        static void __stdcall timer_callback(
            ::PTP_CALLBACK_INSTANCE instance,
            void * context,
            ::PTP_TIMER handle
            )
        {
            (static_cast<T*>(context)->*M)(Hints(instance));
        }
    };

} }

#endif /* _w32_tp_Timer_hpp__ */
