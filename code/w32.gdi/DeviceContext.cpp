// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/DeviceContext.hpp>
#include <w32.gdi/Bitmap.hpp>
#include <w32.gdi/Brush.hpp>
#include <w32.gdi/Device.hpp>
#include <w32.gdi/DeviceCompatibleBitmap.hpp>
#include <w32.gdi/DeviceIndependantBitmap.hpp>
#include <w32.gdi/EnhancedMetafile.hpp>
#include <w32.gdi/ImageList.hpp>
#include <w32.gdi/MappingMode.hpp>
#include <w32.gdi/Metafile.hpp>
#include <w32.gdi/PixelFormat.hpp>
#include <w32.gdi/Point.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Region.hpp>
#include <w32.gdi/Window.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HDC create ( ::LPCWSTR device )
    {
        const ::HDC handle = ::CreateDCW(device,0,0,0);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateDC, error);
        }
        return (handle);
    }

    ::HDC get ( ::HWND window )
    {
        const ::HDC handle = ::GetDC(window);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetDC, error);
        }
        return (handle);
    }

    ::HDC duplicate ( ::HDC model )
    {
        const ::HDC clone = ::CreateCompatibleDC(model);
        if ( clone == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateCompatibleDC, error);
        }
        return (clone);
    }

    void release ( ::HDC object, ::HWND source )
    {
        const ::BOOL result = ::ReleaseDC(source, object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void destroy ( ::HDC object, ::HWND )
    {
        const ::BOOL result = ::DeleteDC(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HDC, ::HWND )
    {
    }

}

namespace w32 { namespace gdi {

    DeviceContext::Handle DeviceContext::claim ( ::HDC object )
    {
        return (Handle(object, Cleanup(&destroy)));
    }

    DeviceContext::Handle DeviceContext::proxy ( ::HDC object )
    {
        return (Handle(object, Cleanup(&abandon)));
    }

    DeviceContext DeviceContext::display ()
    {
        const Handle handle(claim(::create(L"DISPLAY")));
        return (DeviceContext(handle));
    }

    DeviceContext DeviceContext::compatible ( const DeviceContext& other )
    {
        const Handle handle(claim(::duplicate(other.handle())));
        return (DeviceContext(handle));
    }

    DeviceContext::DeviceContext ( const Handle& handle )
        : myHandle(handle)
    {
    }

    DeviceContext::DeviceContext ( const Window& window )
        : myHandle(::get(window.handle()), Cleanup(&::release, window.handle()))
    {
    }

    DeviceContext::DeviceContext ( const string& device )
        : myHandle(claim(::create(device.data())))
    {
    }

    DeviceContext::DeviceContext ( const Device& device )
        : myHandle(claim(::create(device.name().data())))
    {
    }

    const DeviceContext::Handle& DeviceContext::handle () const
    {
        return (myHandle);
    }

    void DeviceContext::set ( const PixelFormat& pixelformat )
    {
        const PixelFormat::Description description(pixelformat);
        const ::BOOL result = ::SetPixelFormat(
            handle(), pixelformat.id(), &description.get()
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetPixelFormat, error);
        }
    }

    void DeviceContext::bitblt (
        const Rectangle& area,
        const DeviceContext& source,
        const Point& origin
        )
    {
        const ::BOOL result = ::BitBlt(
            handle(), area.top(), area.left(),
            area.width(), area.height(), source.handle(),
            origin.x(), origin.y(), SRCCOPY
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(BitBlt,::GetLastError());
        }
    }

    void DeviceContext::stretchblt (
        const Rectangle& darea,
        const DeviceContext& source,
        const Rectangle& sarea
        )
    {
        const ::BOOL result = ::StretchBlt(
            handle(), darea.top(), darea.left(), darea.width(),
            darea.height(), source.handle(), sarea.top(),
            sarea.left(), sarea.width(), sarea.height(), SRCCOPY
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(StretchBlt,::GetLastError());
        }
    }

    MappingMode DeviceContext::mapping () const
    {
        return (MappingMode::of(*this));
    }

    void DeviceContext::invert ( const Region& region )
    {
        if ( ::InvertRgn(handle(), region.handle()) == FALSE ) {
            UNCHECKED_WIN32C_ERROR(InvertRgn,::GetLastError());
        }
    }

    void DeviceContext::cancel ()
    {
        if ( ::CancelDC(handle()) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CancelDC, error);
        }
    }

    void DeviceContext::play ( const Metafile& metafile )
    {
        const ::BOOL result = ::PlayMetaFile(handle(), metafile.handle());
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(PlayMetaFile,::GetLastError());
        }
    }

    void DeviceContext::play (
        const EnhancedMetafile& metafile, const Rectangle& bounds
        )
    {
        const ::BOOL result = ::PlayEnhMetaFile(
            handle(), metafile.handle(), &bounds.data()
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(PlayEnhMetaFile, error);
        }
    }

    void DeviceContext::fill ( const Region& region )
    {
        const ::BOOL result = ::PaintRgn(handle(), region.handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(PaintRgn, error);
        }
    }

    void DeviceContext::fill ( const Region& region, const Brush& brush )
    {
        const ::BOOL result = ::FillRgn(
            handle(), region.handle(), brush.handle()
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FillRgn, error);
        }
    }

    void DeviceContext::frame (
        const Region& region, const Brush& brush, int hborder, int vborder
        )
    {
        const ::BOOL result = ::FrameRgn(
            handle(), region.handle(),
            brush.handle(), hborder, vborder
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FillRgn, error);
        }
    }

    void DeviceContext::draw (
        const ImageList& list, int image, const Point& position
        )
    {
        const ::BOOL result = ImageList_Draw(
            list.handle(), image, handle(),
            position.x(), position.y(), ILD_NORMAL
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(ImageList_Draw,0);
        }
    }

    void DeviceContext::write ( const Point& origin, const string& text )
    {
        const ::BOOL result = ::TextOutW(
            handle(), origin.x(), origin.y(), text.data(), text.size()
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TextOut, error);
        }
    }

    void DeviceContext::put (
        DeviceCompatibleBitmap& target,
        const DeviceIndependantBitmap& source
        )
    {
        const Bitmap::Info info(target);
        const ::DWORD total = info.height();
        ::DWORD copied = 0;
        int result = 0;
        do
        {
                // Copy as many scan lines as possible.
            result = ::SetDIBits(
                handle(), target.handle(), copied,
                total-copied, source.buffer(), &info.data(),
                0 // No color table.
                );
            if ( result == 0 )
            {
                const DWORD error = GetLastError();
                UNCHECKED_WIN32C_ERROR(SetDIBits, error);
            }
        }
            // Start over if succeeded but not finished yet.
        while ((result > 0) && ((copied += result) < total));
    }

    void DeviceContext::get (
        DeviceIndependantBitmap& target,
        const DeviceCompatibleBitmap& source
        )
    {
        const DeviceIndependantBitmap::Guard guard(target);
        
        Bitmap::Info info(source);
        const ::DWORD total = info.height();
        ::DWORD copied = 0;
        int result = 0;
        do
        {
                // Copy as many scan lines as possible.
            result = ::GetDIBits(
                handle(), source.handle(),
                copied, total-copied, target.buffer(), &info.data(),
                0 // No color table.
                );
            if ( result == 0 )
            {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(GetDIBits, error);
            }
        }
            // Start over if succeeded but not finished yet.
        while ((result > 0) && ((copied += result) < total));
    }

    DeviceContext::Cleanup::Cleanup ( Backend backend, ::HWND source )
        : myBackend(backend), mySource(source)
    {
    }

    void DeviceContext::Cleanup::operator() ( ::HDC object ) const
    {
        (*myBackend)(object, mySource);
    }

} }
