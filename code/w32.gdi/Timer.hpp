#ifndef _w32_gdi_Timer_hpp__
#define _w32_gdi_Timer_hpp__

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
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32/Timespan.hpp>
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Windows event loop based alarm.
         */
    class Timer :
        private NotCopyable
    {
        /* nested types. */
    public:
            /*!
             * @brief Native identifier for a timer.
             */
        typedef uintptr Handle;

            /*!
             * @brief Signature for timer callback functions.
             */
        typedef void ( __stdcall * Callback )
            ( ::HWND, ::UINT, ::UINT_PTR, ::DWORD );

            /*!
             * @brief Adapter for function callbacks.
             */
        template<typename P, P F> struct adapt;

        /* data. */
    private:
        ::HWND myWindow;
        Timespan myTimeout;
        Callback myCallback;
        Handle myHandle;

        /* construction. */
    public:
            /*!
             * @brief Creates a new timer with a given @a timeout.
             */
        Timer ( Timespan timeout, Callback callback );

        Timer ( const Window& window, Timespan timeout, Callback callback );

            /*!
             * @brief Releases any acquired resources.
             */
        ~Timer ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the timer's @c Handle.
             * @return The timer's native identifier.
             */
        Handle handle () const;

        Timespan timeout () const;
        void timeout ( Timespan timeout );

        Callback callback () const;
        void callback ( Callback callback );

            /*!
             * @brief Creates a new timer to replace the existing one.
             */
        void reset ();

            /*!
             * @brief Creates a new timer to replace the existing one.
             */
        void reset ( Timespan timeout, Callback callback );
    };

        // Adapter for simple callbacks. This is useful if only a single timer
        // is associated to a callback function.
    template<void(*F)()>
    struct Timer::adapt<void(*)(),F>
    {
        operator Callback () const {
            return (result);
        }
    private:
             // Actual implementation.
        static void __stdcall result
            ( ::HWND, ::UINT, ::UINT_PTR, ::DWORD )
        {
            (*F)();
        }
    };

        // Adapter for callbacks requiring the timer's identifier. This is
        // useful if multiple timers are associated to the same callback.
    template<void(*F)(Timer::Handle)>
    struct Timer::adapt<void(*)(Timer::Handle),F>
    {
        operator Callback () const {
            return (result);
        }
    private:
             // Actual implementation.
        static void __stdcall result
            ( ::HWND hwnd, ::UINT, ::UINT_PTR timer, ::DWORD )
        {
            (*F)(timer);
        }
    };

        // Adapter for callbacks requiring the timer's window. This is
        // useful if multiple timers are associated to the same callback
        // and each is owned by a different window.
    template<void(*F)(Window&)>
    struct Timer::adapt<void(*)(Window&),F>
    {
        operator Callback () const {
            return (result);
        }
    private:
             // Actual implementation.
        static void __stdcall result
            ( ::HWND hwnd, ::UINT, ::UINT_PTR, ::DWORD )
        {
            (*F)(Window(Window::proxy(hwnd)));
        }
    };

        // Adapter for callbacks requiring the timer's window. This is
        // useful if multiple timers are associated to the same callback
        // and more than one may be associated to the same window.
    template<void(*F)(Window&,Timer::Handle)>
    struct Timer::adapt<void(*)(Window&,Timer::Handle),F>
    {
        operator Callback () const {
            return (result);
        }
    private:
             // Actual implementation.
        static void __stdcall result
            ( ::HWND hwnd, ::UINT, ::UINT_PTR timer, ::DWORD )
        {
            (*F)(Window(Window::proxy(hwnd)), timer);
        }
    };


} }

#endif /* _w32_gdi_Timer_hpp__ */
