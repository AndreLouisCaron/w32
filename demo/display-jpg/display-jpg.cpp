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
