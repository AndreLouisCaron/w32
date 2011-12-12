// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
