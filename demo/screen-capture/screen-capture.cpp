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

#include <w32/app/windows-program.hpp>

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

#include <w32/app/windows-program.cpp>
