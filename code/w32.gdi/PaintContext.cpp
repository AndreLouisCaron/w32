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
