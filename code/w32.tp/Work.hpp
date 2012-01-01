#ifndef _w32_tp_Work_hpp__
#define _w32_tp_Work_hpp__

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
        operator ::PTP_WORK_CALLBACK () const
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
            F(Hints(instance), context);
        }
    };

    template<typename T, void(T::*M)(Hints&)>
    struct Work::method
    {
        operator ::PTP_WORK_CALLBACK () const
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
            (static_cast<T*>(context)->*M)(Hints(instance));
        }
    };

} }

#endif /* _w32_tp_Work_hpp__ */
