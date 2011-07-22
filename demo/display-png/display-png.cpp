// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.gdi.hpp>
#include <w32.io.hpp>

#include "png.hpp"

namespace {

    class W32FileSource :
        public png::Source< W32FileSource >
    {
        /* data. */
    private:
        w32::io::InputFile myStream;

        /* construction. */
    public:
        explicit W32FileSource
            ( const w32::string& path ) : myStream(path) {}

        /* methods. */
    public:
        png::size_t get ( png::byte * data, png::size_t size )
        {
            return (myStream.get(data, size));
        }
    };

    struct Factory
    {
        w32::gdi::Image operator() ( png::uint32 w, png::uint32 h ) const
        {
            return (w32::gdi::Image(w32::gdi::Size(w, h), 24));
        }
    };

    const w32::gdi::Image decode ( const w32::string& path )
    {
        W32FileSource stream(path);
        return (png::decode<w32::gdi::Image>(stream, Factory()));
    }

    void quit ()
    {
        w32::gdi::quit();
    }

    w32::gdi::Timer::Callback callback () {
        return (w32::gdi::Timer::adapt<void(*)(),&quit>());
    }

}

#include <w32/gdi/windows-program.hpp>

namespace {

    int run ( const w32::string&, int )
    {
            // Load the test image.
        const w32::gdi::Image image = ::decode(L"lena.png");
        const w32::gdi::Image::Info info(image);
        
            // Create an image box.
        const w32::gdi::Rectangle area
            (50, info.width(), 50, info.height());
        w32::gdi::Static window(area);
        window.bitmap(image);
        window.show();
        
            // Automatically quit the application.
        const w32::Timespan timeout
            (5, w32::Timespan::Unit::second());
        w32::gdi::Timer timer(timeout, ::callback());
        
            // Process events.
        w32::gdi::Event event;
        w32::gdi::ThreadWindowsEvents queue;
        while ( queue.next(event) )
        {
            event.translate();
            event.dispatch();
        }
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/gdi/windows-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.gdi.lib" )
#pragma comment ( lib, "w32.io.lib" )
#pragma comment ( lib, "w32.mt.lib" )

#pragma comment ( lib, "libpng.lib" )
#pragma comment ( lib, "zlib.lib" )
