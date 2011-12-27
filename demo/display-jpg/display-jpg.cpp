// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.gdi.hpp>
#include <w32.io.hpp>

#include "jpeg.hpp"

namespace {

        // Have jpeglib read directly from a `w32::io::InputFile`.
    class W32FileSource :
        public jpeg::Source< W32FileSource >
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
        jpeg::size_t get ( jpeg::byte * data, jpeg::size_t size )
        {
            return (myStream.get(data, size));
        }
    };

        // Have jpeglib read directly into a `w32::gdi::Bitmap`.
    struct Factory
    {
        w32::gdi::Image operator() ( jpeg::size_t w, jpeg::size_t h ) const
        {
            return (w32::gdi::Image(w32::gdi::Size(w, h), 24));
        }
    };

        // Wrap the above into a clean interface.
    const w32::gdi::Image decode ( const w32::string& path )
    {
        W32FileSource stream(path);
        return (jpeg::decode<w32::gdi::Image>(stream, Factory()));
    }

        // Timer callback.
    void quit () { w32::gdi::quit(); }

    w32::gdi::Timer::Callback callback () {
        return (w32::gdi::Timer::adapt<void(*)(),&quit>());
    }

}

#include <w32/gdi/windows-program.hpp>

namespace {

    int run ( const w32::string&, int )
    {
            // Load the test image.
        const w32::gdi::Image image = ::decode(L"lena.jpg");
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
