#ifndef _w32_gdi_Monitor_hpp__
#define _w32_gdi_Monitor_hpp__

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
#include <w32/Error.hpp>
#include <w32.gdi/Device.hpp>
#include <w32.gdi/DeviceContext.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <vector>

namespace w32 { namespace gdi {

    class Point;
    class Window;

    class Monitor
    {
        /* nested types. */
    public:
        typedef Reference< ::HMONITOR > Handle;

        class Info;

        /* class methods. */
    public:
        static Handle proxy ( ::HMONITOR object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Monitor ( const Handle& handle );
        explicit Monitor ( const Window& window );
        explicit Monitor ( const Rectangle& rectangle );
        explicit Monitor ( const Point& point );

        /* methods. */
    public:
        const Handle& handle () const;
    };

    class Monitor::Info
    {
        /* nested types. */
    public:
        typedef ::MONITORINFOEXW Data;

            /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        explicit Info ( const Monitor& monitor );
        explicit Info ( const Window& window );
        Rectangle bounds () const;
        Rectangle area () const;
        bool primary () const;
        string device () const;
    };

    template<typename Op>
    void monitors ( Op op )
    {
        struct _
        {
            static ::BOOL __stdcall enumerate (
                ::HMONITOR hMonitor, ::HDC hdcMonitor,
                ::LPRECT lprcMonitor, ::LPARAM dwData
                )
            {
                Monitor monitor(Monitor::proxy(hMonitor));
                DeviceContext context(DeviceContext::proxy(hdcMonitor));
                Rectangle area(*lprcMonitor);
                Op& op = *reinterpret_cast<Op*>(dwData);
                op(monitor, context, area);
                return (TRUE);
            }
        };
        const ::BOOL result = ::EnumDisplayMonitors(
            0, 0, &_::enumerate, reinterpret_cast< ::LPARAM >(&op)
            );
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(EnumDisplayMonitors, error);
        }
    }

    std::vector< Monitor > monitors ();

} }

#endif /* _w32_gdi_Monitor_hpp__ */
