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

#include <revel.h>

namespace {

    w32::Timespan period ()
    {
        return (w32::Timespan::Timespan(1000/30,
            w32::Timespan::Unit::millisecond()));
    }

    bool is_primary ( const w32::gdi::Monitor& monitor )
    {
        return (w32::gdi::Monitor::Info(monitor).primary());
    }

    w32::gdi::Monitor primary ()
    {
        const std::vector< w32::gdi::Monitor > monitors = w32::gdi::monitors();
        return (*std::find_if(monitors.begin(), monitors.end(), &is_primary));
    }

    int encoder = 0;
    ::Revel_Params encoding;
    ::Revel_VideoFrame frame;

    void capture ( w32::gdi::Window& )
    {
            // Access the primary screen.
        const w32::gdi::Monitor::Info screen(primary());
        w32::gdi::DeviceContext source(screen.device());
        const w32::gdi::Rectangle sarea = screen.bounds();
        
            // Allocate a bitmap to receive frame data.
        const w32::gdi::Rectangle darea(0, frame.width, 0, frame.height);
        w32::gdi::DeviceIndependantBitmap bitmap(darea.span(), 24);
        
            // Copy the screen contents to a bitmap.
        w32::gdi::DeviceContext destination =
            w32::gdi::DeviceContext::compatible(source);
        { const w32::gdi::Bitmap::Selection _(destination, bitmap);
            destination.stretchblt(darea, source, sarea);
        }
        
        frame.pixels = bitmap.buffer();
        const ::Revel_Error error = ::Revel_EncodeFrame(encoder, &frame);
        if ( error == REVEL_ERR_NONE )
        {
            throw (std::exception("REVEL: could not encode frame!"));
        }
    }

    w32::gdi::Timer::Callback callback ()
    {
        return (w32::gdi::Timer::adapt<void(*)(w32::gdi::Window&),&capture>());
    }

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
            window().show();
        }

        /* methods. */
    public:
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
            // Sanity check.
        if ( REVEL_API_VERSION != ::Revel_GetApiVersion() )
        {
            throw (std::exception("REVEL: version mismatch!"));
        }
        ::Revel_Error error = REVEL_ERR_NONE;
        
        error = ::Revel_CreateEncoder(&::encoder);
        if ( ::encoder != REVEL_ERR_NONE )
        {
            throw (std::exception("REVEL: could not create encoder!"));
            return (EXIT_FAILURE);
        }
        
        const w32::gdi::Monitor::Info monitor(::primary());
        
            // Prepare to encode XviD / AVI.
        ::Revel_InitializeParams(&::encoding);
        ::encoding.width = monitor.bounds().width() / 4;
        ::encoding.height = monitor.bounds().height() / 4;
        ::encoding.frameRate = 30.0f;
        ::encoding.quality = 1.0f;
        ::encoding.codec = REVEL_CD_XVID;
        ::encoding.hasAudio = 0;
        ::encoding.audioBits = 16;
        ::encoding.audioChannels = 2;
        ::encoding.audioRate = 22050;
        ::encoding.audioSampleFormat = REVEL_ASF_PCM;
        
            // Create an application window.
        w32::gdi::Class class_(L"Stream my screen!");
        w32::gdi::Registration registration(class_);
        ::MyApplication _(registration);
        
            // Start encoding.
        error = ::Revel_EncodeStart(::encoder, "out.avi", &encoding);
        if ( error != REVEL_ERR_NONE )
        {
            throw (std::exception("REVEL: could not start encoding!"));
            return (EXIT_FAILURE);
        }
        
            // Prepare to receive Windows bitmaps.
        ::frame.width = encoding.width;
        ::frame.height = encoding.height;
        ::frame.bytesPerPixel = 3;
        ::frame.pixelFormat = REVEL_PF_BGR;
        ::frame.pixels = 0;
        
            // Wait until doomsday!
        const w32::wparam status = w32::gdi::loop();
        
            // Cleanup after sloppy C libraries.
        error = ::Revel_EncodeEnd(::encoder);
        if ( error != REVEL_ERR_NONE )
        {
            throw (std::exception("REVEL: could not stop encoding!"));
            return (EXIT_FAILURE);
        }
        
        error = ::Revel_DestroyEncoder(::encoder);
        if ( error != REVEL_ERR_NONE )
        {
            throw (std::exception("REVEL: could not destroy encoder!"));
            return (EXIT_FAILURE);
        }
        
        return (status);
    }

}

#include <w32/gdi/windows-program.cpp>
