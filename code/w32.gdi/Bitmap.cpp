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

#include <w32.gdi/Bitmap.hpp>
#include <w32.gdi/DeviceContext.hpp>
#include <w32.gdi/Size.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    void destroy ( ::HBITMAP object )
    {
        if ( ::DeleteObject(object) == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HBITMAP object )
    {
    }

}

namespace w32 { namespace gdi {

    Bitmap::Handle Bitmap::claim ( ::HBITMAP object )
    {
        return (Bitmap::Handle(object, &::destroy));
    }

    Bitmap::Handle Bitmap::proxy ( ::HBITMAP object )
    {
        return (Bitmap::Handle(object, &::abandon));
    }

    Bitmap::Bitmap ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Bitmap::Handle& Bitmap::handle () const
    {
        return (myHandle);
    }

    Bitmap::Info::Info ( const Bitmap& bitmap )
    {
            // Set standard fields.
        ::ZeroMemory(&myData,sizeof(myData));
        myData.bmiHeader.biSize = sizeof(::BITMAPINFO);
        myData.bmiHeader.biPlanes      = 1;
        myData.bmiHeader.biCompression = BI_RGB;
        
            // Get bitmap info.
        ::BITMAP info;
        const int result = ::GetObject(
            bitmap.handle(), sizeof(info), &info
            );
        if ( result != sizeof(info) ) {
            UNCHECKED_WIN32C_ERROR(GetObject,::GetLastError());
        }
        
            // Set custom fields.
        myData.bmiHeader.biBitCount = info.bmBitsPixel;
        myData.bmiHeader.biWidth    = info.bmWidth;
        myData.bmiHeader.biHeight   = -info.bmHeight;
    }

    Bitmap::Info::Data& Bitmap::Info::data ()
    {
        return (myData);
    }

    const Bitmap::Info::Data& Bitmap::Info::data () const
    {
        return (myData);
    }

    long Bitmap::Info::width () const
    {
        return (myData.bmiHeader.biWidth);
    }

    long Bitmap::Info::height () const
    {
        return (-myData.bmiHeader.biHeight);
    }

    Size Bitmap::Info::size () const
    {
        return (Size(width(), height()));
    }

    word Bitmap::Info::depth () const
    {
        return (myData.bmiHeader.biBitCount);
    }

    Bitmap::Selection::Selection (
        const DeviceContext& device, const Bitmap& bitmap
        )
        : myDevice(device.handle()),
        myPredecessor(::SelectObject(myDevice, bitmap.handle()))
    {
    }

    Bitmap::Selection::~Selection ()
    {
        ::SelectObject(myDevice, myPredecessor);
    }

} }
