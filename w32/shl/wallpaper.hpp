#ifndef _w32_shl_wallpaper_hpp__
#define _w32_shl_wallpaper_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace shl {

        /*!
         * @brief Enumerates ways the system can modify a desktop wallpaper
         *    image when the resolution differs from that of the screen's.
         */
    class W32_SHL_EXPORT WallpaperStyle
    {
        /* class data. */
    public:
        static const WallpaperStyle stretch ();
        static const WallpaperStyle center ();
        static const WallpaperStyle repeat ();

        /* data. */
    private:
        dword myType;
        dword myTiling;

        /* construction.*/
    private:
        WallpaperStyle ( dword type, dword tiling );

        /* methods. */
    public:
        dword type () const;
        dword tiling () const;

        /* operators. */
    public:
        bool operator== ( const WallpaperStyle& rhs ) const;
        bool operator!= ( const WallpaperStyle& rhs ) const;
    };

        /*!
         * @brief Sets the current user's desktop wallpaper.
         *
         * @param image Filesystem path to the image. Only bitmap images are
         *    supported. Starting from Vista, JPEG images are also supported.
         * @param style How to modify the image when the resolution doesn't
         *    match the screen's.
         */
    W32_SHL_EXPORT void wallpaper
        ( const string& image, WallpaperStyle style );

} }

#endif /* _w32_shl_wallpaper_hpp__ */
