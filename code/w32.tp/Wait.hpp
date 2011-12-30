#ifndef _w32_tp_Wait_hpp__
#define _w32_tp_Wait_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32.tp/Queue.hpp>

// See the documentation on thread pools on MSDN, it has a pretty good summary.  There
// are general recommendations in the "best practices" section which merit attention.
//   {{ http://msdn.microsoft.com/en-us/library/windows/desktop/ms686760.aspx }}

namespace w32 { namespace tp {

    class Hints;

    // Use for blocking streams and other waitables (process, ...).
    class Wait
    {
        /* nested types. */
    public:
        template<void(*F)(Hints&,void*)> struct function;
        template<typename T, void(T::*M)(Hints&)> struct method;

        typedef Reference<::PTP_WAIT> Handle;

        /* class methods. */
    private:
        static ::PTP_WAIT setup
        ( ::PTP_CALLBACK_ENVIRON queue, ::HANDLE waitable,
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

        template<void(*F)(Hints&,void*)>
        Wait ( Queue& queue, ::HANDLE waitable,
               function<F> function, void * context=0 )
            : myHandle(claim(setup(&queue.data(), waitable, function, context)))
        {
        }

        template<typename T, void(T::*M)(Hints&)>
        Wait ( Queue& queue, ::HANDLE waitable, T& object, method<T,M> method )
            : myHandle(claim(setup(&queue.data(), waitable, method, &object)))
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
            F(Hints(instance), context);
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
            (static_cast<T*>(context)->*M)(Hints(instance));
        }
    };

} }

#endif /* _w32_tp_Wait_hpp__ */
