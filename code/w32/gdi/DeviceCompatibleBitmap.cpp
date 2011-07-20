// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/DeviceCompatibleBitmap.hpp>
#include <w32/gdi/DeviceContext.hpp>
#include <w32/gdi/Size.hpp>
#include <w32/Error.hpp>

namespace {

    ::HBITMAP create ( ::HDC context, const ::SIZE& size )
    {
        const ::HBITMAP handle = ::CreateCompatibleBitmap(
            context, size.cx, size.cy
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateCompatibleBitmap, error);
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    DeviceCompatibleBitmap::DeviceCompatibleBitmap
        ( const DeviceContext& context, const Size& size )
        : Bitmap(claim(::create(context.handle(), size.data())))
    {
    }

} }
