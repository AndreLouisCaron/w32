#ifndef _w32_gdi_Timer_hpp__
#define _w32_gdi_Timer_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32/Timespan.hpp>
#include <w32/gdi/Window.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Windows event loop based alarm.
         */
    class W32_GDI_EXPORT Timer :
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
