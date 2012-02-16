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

#include <w32.shl/wallpaper.hpp>
#include <w32.hpp>
#include <w32.rgs.hpp>
#include <string>
#include <sstream>

namespace {

    using namespace w32;
    using namespace w32::rgs;

    string itoa ( dword value )
    {
        std::wostringstream format;
        format << value;
        return (format.str().c_str());
    }

    void image ( const string& path )
    {
        const ::DWORD flags = SPIF_UPDATEINIFILE|SPIF_SENDWININICHANGE;
        const ::BOOL result = ::SystemParametersInfoW(
            SPI_SETDESKWALLPAPER, 0, (::LPVOID)path.c_str(), flags
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error != NO_ERROR ) {
                UNCHECKED_WIN32C_ERROR(SystemParametersInfo, error);
            }
        }
    }

    void settings ( const string& path, dword style, dword tiling )
    {
            // Access settings in the registry.
        Key desktop(Key::user(), L"Control Panel\\Desktop");
        Value WallpaperStyle(desktop, L"WallpaperStyle");
        Value TileWallpaper(desktop, L"TileWallpaper");
        Value Wallpaper(desktop, L"Wallpaper");
        
            // Set style.
        WallpaperStyle = itoa(style);
        TileWallpaper = itoa(tiling);
        Wallpaper = path;
        
            // Commit changes.
        desktop.flush();
        
            // Always change image *after* changing settings.
        image(path);
    }

        // This keeps shooting errors on Vista.
#if 0
    void broadcast ()
    {
        const ::BOOL result = ::PostMessage(
            ::GetDesktopWindow(), WM_SETTINGCHANGE, 0, 0
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error != NO_ERROR ) {
                UNCHECKED_WIN32C_ERROR(PostMessage, error);
            }
        }
    }
#endif

}

namespace w32 { namespace shl {

    const WallpaperStyle WallpaperStyle::stretch ()
    {
        return (WallpaperStyle(2, 0));
    }

    const WallpaperStyle WallpaperStyle::center ()
    {
        return (WallpaperStyle(1, 0));
    }

    const WallpaperStyle WallpaperStyle::repeat ()
    {
        return (WallpaperStyle(1, 1));
    }

    WallpaperStyle::WallpaperStyle ( dword type, dword tiling )
        : myType(type), myTiling(tiling)
    {
    }

    dword WallpaperStyle::type () const
    {
        return (myType);
    }

    dword WallpaperStyle::tiling () const
    {
        return (myTiling);
    }

    bool WallpaperStyle::operator== ( const WallpaperStyle& rhs ) const
    {
        return ((myType == rhs.myType)
            && (myTiling == rhs.myTiling));
    }

    bool WallpaperStyle::operator!= ( const WallpaperStyle& rhs ) const
    {
        return ((myType != rhs.myType)
            && (myTiling != rhs.myTiling));
    }

    void wallpaper ( const string& image, WallpaperStyle style )
    {
        ::settings(image.data(), style.type(), style.tiling());
    }

} }
