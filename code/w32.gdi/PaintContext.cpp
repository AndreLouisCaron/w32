// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/PaintContext.hpp>
#include <w32.gdi/DeviceContext.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Window.hpp>

namespace {

    ::HDC begin ( ::HWND window, ::PAINTSTRUCT& data )
    {
        const ::HDC device = ::BeginPaint(window, &data);
        if ( device == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(BeginPaint, error);
        }
        return (device);
    }

}

namespace w32 { namespace gdi {

    PaintContext::PaintContext ( Window& window )
        : myData(),
          myDevice(DeviceContext::proxy(::begin(window.handle(), myData)))
    {
    }

    PaintContext::Data& PaintContext::data ()
    {
        return (myData);
    }

    const PaintContext::Data& PaintContext::data () const
    {
        return (myData);
    }

    DeviceContext PaintContext::device () const
    {
        return (myDevice);
    }

    bool PaintContext::erase () const
    {
        return (myData.fErase != 0);
    }

    Rectangle PaintContext::area () const
    {
        return (Rectangle(myData.rcPaint));
    }

} }
