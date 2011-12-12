#ifndef _w32_gdi_Monitor_hpp__
#define _w32_gdi_Monitor_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
