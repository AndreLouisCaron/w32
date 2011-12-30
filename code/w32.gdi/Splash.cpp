// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
