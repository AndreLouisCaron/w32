#ifndef _w32_tp_Queue_hpp__
#define _w32_tp_Queue_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
