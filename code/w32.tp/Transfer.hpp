#ifndef _w32_tp_Transfer_hpp__
#define _w32_tp_Transfer_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.tp/Queue.hpp>

namespace w32 { namespace tp {

    class Hints;

    // Use for notification of completion of overlapped I/O operations.
    // This object only handles notifications.  I/O operations must be
    // started using regular overlapped I/O operations (e.g. "ReadFile()").
    //
    // Don't use a stream with FILE_SKIP_COMPLETION_PORT_ON_SUCCESS
    // notification mode.
    class Transfer
    {
        /* nested types. */
    public:
        class Result;

        template<void(*)(Hints&,void*,Result)> struct function;
        template<typename T, void(T::*M)(Hints&,Result)> struct method;

        /* class methods. */
    private:
        static ::PTP_IO setup
        ( ::PTP_CALLBACK_ENVIRON queue, ::HANDLE stream,
          ::PTP_WIN32_IO_CALLBACK callback, void * context );

        /* data. */
    private:
        ::PTP_IO myHandle;

        /* construction. */
    public:
        template<void(*F)(Hints&,void*,Result)>
        Transfer ( Queue& queue, ::HANDLE stream,
                   function<F> function, void * context=0 )
            : myHandle(setup(&queue.data(), stream, function, context))
        {
        }

        template<typename T, void(T::*M)(Hints&,Result)>
        Transfer ( Queue& queue, ::HANDLE stream,
                   T& object, method<T,M> method )
            : myHandle(setup(&queue.data(), stream, method, &object))
        {
        }

        ~Transfer ();

        /* methods. */
    public:
        // Call if I/O operation fails.
        void cancel ();
        void wait ( bool cancel_pending=false );
    };

    class Transfer::Result
    {
        /* data. */
    private:
        void * myOverlapped;
        ::ULONG myStatus;
        ::ULONG_PTR mySize;

        /* construction. */
    public:
        Result ( void * overlapped, ::ULONG status, ::ULONG_PTR size )
            : myOverlapped(overlapped), myStatus(status), mySize(size)
        {
        }

    public:
        // if succeeded() returns false, this contains a system error code.
        ::ULONG status () const
        {
            return (myStatus);
        }

        bool succeeded () const
        {
            return (status() == NO_ERROR);
        }

        // number of bytes transferred as part of the completed I/O operation.
        ::ULONG_PTR size () const
        {
            return (mySize);
        }

        // native asynchronous I/O state.  may now be used to
        // start another transfer.  clear before using again.
        ::OVERLAPPED& transfer ()
        {
            return (*static_cast<::OVERLAPPED*>(myOverlapped));
        }
    };

    template<void(*F)(Hints&,void*,Transfer::Result)>
    struct Transfer::function
    {
        operator ::PTP_WIN32_IO_CALLBACK () const
        {
            return (&work_callback);
        }

    private:
        static void __stdcall transfer_callback(
            ::PTP_CALLBACK_INSTANCE instance,
            void * context,
            void * overlapped,
            ::ULONG result,
            ::ULONG_PTR size,
            ::PTP_IO handle
            )
        {
            F(Hints(instance), context, Result(overlapped,result,size));
        }
    };

    template<typename T, void(T::*M)(Hints&,Transfer::Result)>
    struct Transfer::method
    {
        operator ::PTP_WIN32_IO_CALLBACK () const
        {
            return (&transfer_callback);
        }

    private:
        static void __stdcall transfer_callback(
            ::PTP_CALLBACK_INSTANCE instance,
            void * context,
            void * overlapped,
            ::ULONG result,
            ::ULONG_PTR size,
            ::PTP_IO handle
            )
        {
            (static_cast<T*>(context)->*M)
                (Hints(instance), Result(overlapped,result,size));
        }
    };

} }

#endif /* _w32_tp_Transfer_hpp__ */
