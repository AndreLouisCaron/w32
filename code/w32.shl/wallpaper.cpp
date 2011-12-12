// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
