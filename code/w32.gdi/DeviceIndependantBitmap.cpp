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

#include <w32.gdi/DeviceIndependantBitmap.hpp>
#include <w32.gdi/DeviceContext.hpp>
#include <w32/Error.hpp>
#include <w32/astring.hpp>
#include <fstream>

namespace {

    ::HBITMAP allocate (
        const w32::gdi::DeviceContext& device,
        const w32::gdi::Size& size,
        const ::WORD& depth
        )
    {
            // Create a native description of the bitmap.
        ::BITMAPINFO info;
        ::ZeroMemory(&info,sizeof(info));
        info.bmiHeader.biSize        = sizeof(::BITMAPINFO);
        info.bmiHeader.biWidth       = size.width();
        info.bmiHeader.biHeight      = -size.height();
        info.bmiHeader.biPlanes      = 1;
        info.bmiHeader.biBitCount    = depth;
        info.bmiHeader.biCompression = BI_RGB;
        
            // Allocate it.
        void * buffer = 0;
        const ::HBITMAP handle = ::CreateDIBSection(
            device.handle(), &info, DIB_RGB_COLORS, &buffer, 0, 0
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateDIBSection, error);
        }
        else if ( handle == (::HBITMAP)ERROR_INVALID_PARAMETER)
        {
            const ::DWORD error = ERROR_INVALID_PARAMETER;
            UNCHECKED_WIN32C_ERROR(CreateDIBSection, error);
        }
        
        return (handle);
    }

    ::HBITMAP load ( ::LPCWSTR path )
    {
        const ::HBITMAP handle = (::HBITMAP)::LoadImageW(
            0, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION
            );
        if ( handle == NULL )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LoadImage, error);
        }
        return (handle);
    }

    ::HBITMAP copy (
        const w32::gdi::Bitmap& image, const w32::gdi::Size& size
        )
    {
        const ::HBITMAP handle = reinterpret_cast<::HBITMAP>(::CopyImage(
            image.handle(), IMAGE_BITMAP, size.width(), size.height(),
            LR_CREATEDIBSECTION
            ));
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CopyImage, error);
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    DeviceIndependantBitmap::DeviceIndependantBitmap ( const Handle& handle )
        : Bitmap(handle)
    {
    }

    DeviceIndependantBitmap::DeviceIndependantBitmap (
        const DeviceContext& device, const Size& size, ::WORD depth
        )
        : Bitmap(Bitmap::claim(::allocate(device,size,depth)))
    {
    }

    DeviceIndependantBitmap::DeviceIndependantBitmap
        ( const Size& size, ::WORD depth )
        : Bitmap(Bitmap::claim(::allocate(
        DeviceContext::display(), size, depth
        )))
    {
    }

    DeviceIndependantBitmap::DeviceIndependantBitmap (
        const Bitmap& image, const Size& size
        )
        : Bitmap(Bitmap::claim(::copy(image,size)))
    {
    }

    void * DeviceIndependantBitmap::buffer ()
    {
        return (Info(*this).buffer());
    }

    const void * DeviceIndependantBitmap::buffer () const
    {
        return (Info(*this).buffer());
    }

    void DeviceIndependantBitmap::save ( const string& file ) const
    {
            // Obtain info about the current bitmap.
        const Bitmap::Info info(*this);
        
            // Save the info abount the bitmap header
            // in it's raw file layout.
        ::BITMAPINFOHEADER infoheader;
        infoheader.biSize = sizeof(::BITMAPINFOHEADER);
        infoheader.biWidth = info.width();
        infoheader.biHeight = -info.height();
        infoheader.biPlanes = 1;
        infoheader.biCompression = BI_RGB;
        infoheader.biBitCount = info.depth();
        infoheader.biSizeImage =
            infoheader.biWidth * -infoheader.biHeight
            * (infoheader.biBitCount / 8);
        infoheader.biXPelsPerMeter = 0;
        infoheader.biYPelsPerMeter = 0;
        infoheader.biClrUsed = 0;
        infoheader.biClrImportant = 0;
        
            // Fill in the file header.
        ::BITMAPFILEHEADER fileheader;
        fileheader.bfType = 0x4d42;
        fileheader.bfOffBits =
            sizeof(::BITMAPFILEHEADER) + sizeof(::BITMAPINFOHEADER);
        fileheader.bfSize = fileheader.bfOffBits + infoheader.biSizeImage;
        fileheader.bfReserved1 = 0;
        fileheader.bfReserved2 = 0;
        
            // Write everything out to the file.
        astring path = file;
        std::ofstream out(path.data(), std::ios::binary);
        out.write((const char*)&fileheader,sizeof(fileheader));
        out.write((const char*)&infoheader,sizeof(infoheader));
        out.write((const char*)buffer(),infoheader.biSizeImage);
    }

    DeviceIndependantBitmap::Info::Info (
        const DeviceIndependantBitmap& bitmap
        )
    {
        const int result = ::GetObject(
            bitmap.handle(), sizeof(myData), &myData
            );
        if ( result != sizeof(myData) ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetObject, error);
        }
    }

    DeviceIndependantBitmap::Info::Data&
        DeviceIndependantBitmap::Info::data ()
    {
        return (myData);
    }

    const DeviceIndependantBitmap::Info::Data&
        DeviceIndependantBitmap::Info::data () const
    {
        return (myData);
    }

    long DeviceIndependantBitmap::Info::width () const
    {
        return (myData.dsBmih.biWidth);
    }

    long DeviceIndependantBitmap::Info::height () const
    {
        return (-myData.dsBmih.biHeight);
    }

    word DeviceIndependantBitmap::Info::depth () const
    {
        return (myData.dsBmih.biBitCount);
    }

    void * DeviceIndependantBitmap::Info::buffer () const
    {
        return (myData.dsBm.bmBits);
    }

    DeviceIndependantBitmap::Guard::Guard ( DeviceIndependantBitmap& bitmap )
    {
        if ( ::GdiFlush() == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GdiFlush, error);
        }
    }

    FileBitmap::FileBitmap ( const string& path )
        : DeviceIndependantBitmap(Bitmap::claim(
        ::load(path.c_str())
        ))
    {
    }

    void * FileBitmap::buffer ()
    {
        const Info info(*this);
        return (info.buffer());
    }

    const void * FileBitmap::buffer () const
    {
        const Info info(*this);
        return (info.buffer());
    }

    FileBitmap::Info::Info ( const FileBitmap& bitmap )
    {
        const int result = ::GetObject(
            bitmap.handle(), sizeof(myData), &myData
            );
        if ( result != sizeof(myData) )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetObject, error);
        }
    }

    Size FileBitmap::Info::size () const
    {
        return (Size(myData.bmWidth, myData.bmHeight));
    }

    word FileBitmap::Info::depth () const
    {
        return (myData.bmBitsPixel);
    }

    void * FileBitmap::Info::buffer () const
    {
        return (myData.bmBits);
    }

} }
