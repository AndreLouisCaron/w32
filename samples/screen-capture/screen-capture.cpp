// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.gdi.hpp>
#include <w32.mt.hpp>
#include <functional>

namespace {

    w32::Timespan period ()
    {
        return (w32::Timespan::Timespan(100,
            w32::Timespan::Unit::millisecond()));
    }

    bool is_primary ( const w32::gdi::Monitor& monitor )
    {
        return (w32::gdi::Monitor::Info(monitor).primary());
    }

    bool is_secondary ( const w32::gdi::Monitor& monitor )
    {
        const w32::gdi::Monitor::Info properties(monitor);
        const w32::gdi::Device device(properties.device());
        return (device.desktop() && !device.primary());
    }

    w32::gdi::Monitor primary ()
    {
        const std::vector< w32::gdi::Monitor > monitors = w32::gdi::monitors();
        return (*std::find_if(monitors.begin(), monitors.end(), &is_primary));
    }

    w32::gdi::Monitor secondary ()
    {
        const std::vector< w32::gdi::Monitor > monitors = w32::gdi::monitors();
        const std::vector< w32::gdi::Monitor >::const_iterator match
            = std::find_if(monitors.begin(), monitors.end(), &is_secondary);
        if ( match == monitors.end() ) {
            return (primary());
        }
        return (*match);
    }

    void capture ( w32::gdi::Window& window )
    {
        window.invalidate();
    }

    w32::gdi::Timer::Callback callback ()
    {
        return (w32::gdi::Timer::adapt<void(*)(w32::gdi::Window&),&capture>());
    }

        // Mediator, handling coordination between widgets.
    class MyApplication :
        public w32::gdi::Application< MyApplication >
    {
        /* data. */
    private:
        w32::gdi::Timer myTimer;

        /* construction. */
    public:
        MyApplication ( const w32::gdi::Registration& registration )
            : w32::gdi::Application< MyApplication >(registration, *this),
              myTimer(window(), period(), callback())
        {
                // Don't show system bar.
            w32::gdi::Window::Style style = window().style();
            style &= w32::gdi::Window::Style::popupWindow();
            window().style(style);
            
                // Center the window onto the secondary screen.
            //w32::gdi::Monitor::Info monitor(window());
            const w32::gdi::Monitor::Info monitor(secondary());
            window().bounds(monitor.bounds().center(window().bounds()));
            
                // Everything is set up, show thyself!
            /*window().maximize();*/ window().show();
        }

        /* methods. */
    public:
        bool paint ()
        {
                // Access the primary screen.
            const w32::gdi::Monitor::Info screen(primary());
            w32::gdi::DeviceContext source(screen.device());
            
                // Start the paint operation for the window.
            w32::gdi::PaintContext painter(window());
            
                // Custom painting, copy the entire window...
            const w32::gdi::Point origin(0, 0);
            const w32::gdi::Rectangle sarea(origin, screen.bounds().span());
            const w32::gdi::Rectangle darea(origin, window().bounds().span());
            painter.device().stretchblt(darea, source, sarea);
            
            return (true);
        }

        bool syskeyup ( w32::uint code, w32::dword )
        {
            if ( code == VK_F4 ) {
                w32::gdi::quit(); return (true);
            }
            return (false);
        }
    };

}

#include <w32/gdi/windows-program.hpp>

namespace {

    int run ( const w32::string& command, int )
    {
            // Create an application window.
        w32::gdi::Class class_(L"My 1st Window");
        w32::gdi::Registration registration(class_);
        ::MyApplication _(registration);
        
            // Wait until doomsday!
        return (w32::gdi::loop());
    }

}

#include <w32/gdi/windows-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.gdi.lib" )
#pragma comment ( lib, "w32.mt.lib" )
