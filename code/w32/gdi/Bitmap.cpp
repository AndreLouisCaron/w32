// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Bitmap.hpp>
#include <w32/gdi/DeviceContext.hpp>
#include <w32/gdi/Size.hpp>
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
