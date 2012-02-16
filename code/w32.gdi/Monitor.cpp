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

#include <w32.gdi/Monitor.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>
#include <w32.gdi/Point.hpp>
#include <w32.gdi/Window.hpp>
#include <functional>

namespace {

    // Calls container.push_back(argument).
    template<typename Container>
    class BackInserter :
        public std::unary_function< typename Container::value_type, void >
    {
        /* data. */
    private:
        Container& myContainer;

        /* construction. */
    public:
        explicit BackInserter ( Container& container )
            : myContainer(container)
        {}

        /* operators. */
    public:
        template<typename T, typename U>
        result_type operator()
        ( const argument_type& argument, const T&, const U& )
        {
            myContainer.push_back(argument);
        }
    };

    template<typename Container>
    BackInserter< Container > back_inserter ( Container& container )
    {
        return (BackInserter< Container >(container));
    }

    void abandon ( ::HMONITOR object )
    {
    }

    ::HMONITOR intersecting ( ::HWND window )
    {
        return (::MonitorFromWindow(window, MONITOR_DEFAULTTOPRIMARY));
    }

    ::HMONITOR intersecting ( const ::RECT& area )
    {
        return (::MonitorFromRect(&area, MONITOR_DEFAULTTOPRIMARY));
    }

    ::HMONITOR intersecting ( const ::POINT& point )
    {
        return (::MonitorFromPoint(point, MONITOR_DEFAULTTOPRIMARY));
    }

}

namespace w32 { namespace gdi {

    Monitor::Handle Monitor::proxy ( ::HMONITOR object )
    {
        return (Handle(object, &::abandon));
    }

    Monitor::Monitor ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Monitor::Monitor ( const Window& window )
        : myHandle(proxy(::intersecting(window.handle())))
    {
    }

    Monitor::Monitor ( const Rectangle& area )
        : myHandle(proxy(::intersecting(area.data())))
    {
    }

    Monitor::Monitor ( const Point& point )
        : myHandle(proxy(::intersecting(point.data())))
    {
    }

    const Monitor::Handle& Monitor::handle () const
    {
        return (myHandle);
    }

    Monitor::Info::Info ( const Monitor& monitor )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.cbSize = sizeof(myData);
        const ::BOOL result = ::GetMonitorInfoW(monitor.handle(), &myData);
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetMonitorInfo, error);
        }
    }

    Monitor::Info::Info ( const Window& window )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.cbSize = sizeof(myData);
        const ::BOOL result = ::GetMonitorInfoW(
            w32::gdi::Monitor(window).handle(), &myData);
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetMonitorInfo, error);
        }
    }

    Rectangle Monitor::Info::bounds () const
    {
        return (Rectangle(myData.rcMonitor));
    }

    Rectangle Monitor::Info::area () const
    {
        return (Rectangle(myData.rcWork));
    }

    bool Monitor::Info::primary () const
    {
        return ((myData.dwFlags & MONITORINFOF_PRIMARY) != 0);
    }

    string Monitor::Info::device () const
    {
        return (myData.szDevice);
    }

    std::vector< Monitor > monitors ()
    {
        std::vector< Monitor > results;
        monitors(::back_inserter(results));
        return (results);
    }

} }
