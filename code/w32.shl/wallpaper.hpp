#ifndef _w32_shl_wallpaper_hpp__
#define _w32_shl_wallpaper_hpp__

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

#include "__configure__.hpp"

namespace w32 { namespace shl {

        /*!
         * @brief Enumerates ways the system can modify a desktop wallpaper
         *    image when the resolution differs from that of the screen's.
         */
    class WallpaperStyle
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
    void wallpaper
        ( const string& image, WallpaperStyle style );

} }

#endif /* _w32_shl_wallpaper_hpp__ */
