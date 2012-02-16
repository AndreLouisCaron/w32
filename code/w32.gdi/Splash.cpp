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

#include <w32.gdi/Splash.hpp>
#include <w32.gdi/Bitmap.hpp>
#include <w32.gdi/loop.hpp>
#include <w32.gdi/post.hpp>
#include <w32.gdi/Quit.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Static.hpp>
#include <w32.gdi/Window.hpp>

namespace {

    w32::dword do_splash_screen ( void * context )
    {
            // Fetch instance data: this is a static function (yuck)!
        w32::gdi::Bitmap& background =
            *static_cast< w32::gdi::Bitmap* >(context);
            
            // Create a window showing our application logo.
        const w32::gdi::Bitmap::Info info(background);
        const w32::gdi::Rectangle bounds(w32::gdi::Point(0, 0), info.size());
        w32::gdi::Window window(bounds, w32::gdi::Window::Style().popup());
        w32::gdi::Static imagebox(window, w32::gdi::Rectangle(0, 100, 0, 100));
        imagebox.bitmap(background), imagebox.show();
            
            // Display the window while we wait...
        window.show(), w32::gdi::loop();

        return (0);
    }

    w32::mt::Thread::Function callback ()
    {
        return (w32::mt::Thread::function<&do_splash_screen>());
    }

}

namespace w32 { namespace gdi {

    Splash::Splash ( const string& path )
        : myBackground(path),
        myThread(callback(), &static_cast<Bitmap&>(myBackground))
    {
    }

    Splash::~Splash ()
    {
            // Force the application to close.
        w32::gdi::post(myThread, w32::gdi::Quit());
        
            // Wait until the splash screen thread terminates.
        myThread.join();
    }


} }
