// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/PixelFormat.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    PixelFormat::PixelFormat ( const DeviceContext& device )
        : myDevice(device),
          myId(::GetPixelFormat(myDevice.handle()))
    {
        if ( myId == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetPixelFormat, error);
        }
    }

    PixelFormat::PixelFormat ( const DeviceContext& device, const Search& search )
        : myDevice(device),
          myId(::ChoosePixelFormat(myDevice.handle(), &search.criterion()))
    {
        if ( myId == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ChoosePixelFormat, error);
        }
    }

    const PixelFormat::Color PixelFormat::Color::rgba(PFD_TYPE_RGBA);
    const PixelFormat::Color PixelFormat::Color::indexed(PFD_TYPE_COLORINDEX);

    const PixelFormat::Buffering PixelFormat::Buffering::single(0);
    const PixelFormat::Buffering PixelFormat::Buffering::doubled(PFD_DOUBLEBUFFER);
    const PixelFormat::Buffering PixelFormat::Buffering::any(PFD_DOUBLEBUFFER_DONTCARE);

    const PixelFormat::Implementation PixelFormat::Implementation::software(PFD_GENERIC_FORMAT);
    const PixelFormat::Implementation PixelFormat::Implementation::hardware(PFD_GENERIC_ACCELERATED);

    const PixelFormat::Layer PixelFormat::Layer::underlay(PFD_UNDERLAY_PLANE);
    const PixelFormat::Layer PixelFormat::Layer::main(PFD_MAIN_PLANE);
    const PixelFormat::Layer PixelFormat::Layer::overlay(PFD_OVERLAY_PLANE);

    const PixelFormat::Channels PixelFormat::Channels::mono(0);
    const PixelFormat::Channels PixelFormat::Channels::stereo(PFD_STEREO);
    const PixelFormat::Channels PixelFormat::Channels::any(PFD_STEREO_DONTCARE);

    PixelFormat::Description::Description ( const PixelFormat& format )
    {
        myData.nSize = sizeof(myData);
        myData.nVersion = 1;
        const int result = ::DescribePixelFormat(
            format.device().handle(), format.myId, myData.nSize, &myData
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(DescribePixelFormat, error);
        }
    }

} }
