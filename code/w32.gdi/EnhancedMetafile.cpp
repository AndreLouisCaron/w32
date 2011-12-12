// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/EnhancedMetafile.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Size.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>

namespace {

    ::HENHMETAFILE open ( ::LPCWSTR path )
    {
        const ::HENHMETAFILE handle = ::GetEnhMetaFileW(path);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetEnhMetaFile, error);
        }
        return (handle);
    }

    ::HDC create (
        const ::SIZE& size, ::LPCWSTR path, ::LPCWSTR description, ::HDC device
        )
    {
        const int wm = ::GetDeviceCaps(device, HORZSIZE);
        const int hm = ::GetDeviceCaps(device, VERTSIZE);
        const int wp = ::GetDeviceCaps(device, HORZRES);
        const int hp = ::GetDeviceCaps(device, VERTRES);
        const ::RECT area = {
            0, 0, (size.cx * wm * 100) / wp, (size.cy * hm * 100) / hp
        };
        const ::HDC handle = ::CreateEnhMetaFileW
            (device, path, &area, description);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetEnhMetaFile, error);
        }
        return (0);
    }

    ::HENHMETAFILE close ( ::HDC object )
    {
        const ::HENHMETAFILE handle = ::CloseEnhMetaFile(object);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetEnhMetaFile, error);
        }
        return (handle);
    }

    void abandon ( ::HENHMETAFILE object ) {}
    void destroy ( ::HENHMETAFILE object )
    {
        const ::BOOL result = ::DeleteEnhMetaFile(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace gdi {

    EnhancedMetafile::Handle EnhancedMetafile::claim ( ::HENHMETAFILE object )
    {
        return (Handle(object, &::destroy));
    }

    EnhancedMetafile::Handle EnhancedMetafile::proxy ( ::HENHMETAFILE object )
    {
        return (Handle(object, &::abandon));
    }

        static EnhancedMetafile open ( const string& path );

    EnhancedMetafile::EnhancedMetafile ( const Handle& handle )
        : myHandle(handle)
    {
    }

#if 0
    EnhancedMetafile::EnhancedMetafile ( const Size& size, const string& path )
        : myHandle(claim(::create(
              size.data(), path.data(), 0, 0
              )))
    {
    }

    EnhancedMetafile::EnhancedMetafile
        ( const Size& size, const string& path, const string& description )
        : myHandle(claim(::create(
              size.data(), path.data(), description.data(), 0
              )))
    {
    }
#endif

    const EnhancedMetafile::Handle& EnhancedMetafile::handle () const
    {
        return (myHandle);
    }

} }
