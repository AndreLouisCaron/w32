#ifndef _w32_tp_Transfer_hpp__
#define _w32_tp_Transfer_hpp__

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
     * @brief Registration for notification of I/O completion events.
     *
     * Use for notification of completion of overlapped I/O operations.
     * This object only handles notifications.  I/O operations must be
     * started using regular overlapped I/O operations (e.g. @c ReadFile()).
     *
     * @warning Don't use a stream with the @c
     *  FILE_SKIP_COMPLETION_PORT_ON_SUCCESS notification mode.
     */
    class Transfer
    {
        /* nested types. */
    public:
        class Result;

        template<void(*)(Hints&,void*,Result)> struct function;
        template<typename T, void(T::*M)(Hints&,Result)> struct method;

        typedef Reference<::PTP_IO> Handle;

        /* class methods. */
    private:
        static ::PTP_IO setup
        ( ::PTP_CALLBACK_ENVIRON queue, ::HANDLE stream,
          ::PTP_WIN32_IO_CALLBACK callback, void * context );

    public:
        static Handle claim ( ::PTP_IO object );
        static Handle proxy ( ::PTP_IO object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Transfer ( const Handle& handle );

        template<void(*F)(Hints&,void*,Result)>
        Transfer ( Queue& queue, ::HANDLE stream,
                   function<F> function, void * context=0 )
            : myHandle(claim(setup(&queue.data(), stream, function, context)))
        {
        }

        template<typename T, void(T::*M)(Hints&,Result)>
        Transfer ( Queue& queue, ::HANDLE stream,
                   T& object, method<T,M> method )
            : myHandle(claim(setup(&queue.data(), stream, method, &object)))
        {
        }

        /* methods. */
    public:
        const Handle& handle () const;

        void start ();

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

        bool failed () const
        {
            return (myStatus != NO_ERROR);
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
            ::ULONG status,
            ::ULONG_PTR size,
            ::PTP_IO handle
            )
        {
            try {
                F(Hints(instance), context, Result(overlapped,status,size));
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
            ::ULONG status,
            ::ULONG_PTR size,
            ::PTP_IO handle
            )
        {
            try {
                (static_cast<T*>(context)->*M)
                    (Hints(instance), Result(overlapped,status,size));
            }
            catch (const w32::Error& error)
            {
                std::cerr
                    << "Transfer handler: windows error " << error.code() << "."
                    << std::endl;
            }
            catch ( ... )
            {
                std::cerr
                    << "Exception raised from transfer handler."
                    << std::endl;
            }
        }
    };

} }

#endif /* _w32_tp_Transfer_hpp__ */
