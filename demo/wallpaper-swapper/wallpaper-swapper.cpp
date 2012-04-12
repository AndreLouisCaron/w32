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

#include <w32.hpp>
#include <w32.fs.hpp>
#include <w32.gdi.hpp>
#include <w32.rgs.hpp>
#include <w32.shl.hpp>
#include <algorithm>
#include <vector>
#include <ctime>

#include <w32/app/taskbar-application.hpp>

namespace {

    void BrowseForLibrary ();

        /*!
         * @brief List of paths to images.
         */
    std::vector<w32::string> __wallpapers__;

        /*!
         * @brief Timer to get notified of when to change the wallpaper.
         */
    w32::gdi::Timer * __timer__ = 0;

        /*!
         * @brief Loads the path to the wallpaper library.
         */
    w32::string __library__ ()
    {
        w32::rgs::Key key(w32::rgs::Key::user(),
            L"SOFTWARE\\Andre Caron\\Wallpaper Swapper");
        return (w32::rgs::Value(key, L"Library"));
    }

        /*!
         * @brief Saves the path to the wallpaper library.
         */
    void __library__ ( const w32::string& path )
    {
        w32::rgs::Key key(w32::rgs::Key::user(),
            L"SOFTWARE\\Andre Caron\\Wallpaper Swapper");
        w32::rgs::Value _(key, L"Library"); _ = path;
    }

        /*!
         * @brief Timer callback to change the desktop wallpaper.
         */
    void __stdcall Swap ( ::HWND=0, ::UINT=0, ::UINT_PTR=0, ::DWORD=0 )
    {
        static const w32::shl::WallpaperStyle style =
            w32::shl::WallpaperStyle::stretch();
        
            // Load a random image.
        w32::gdi::Image image(w32::gdi::Image::proxy(0));
        while ((image.handle() == 0) && (__wallpapers__.size() > 0))
        {
            const std::size_t i = std::rand() % __wallpapers__.size();
            image = w32::gdi::FileBitmap(__wallpapers__[i]);
            
                // Remove failing images from the list.
            if ( image.handle() == 0 ) {
                __wallpapers__.erase(__wallpapers__.begin() + i);
            }
        }
        
            // Do nothing if we don't have any wallpapers to switch to.
        if ( __wallpapers__.size() < 1 ) {
            return;
        }
        
            // Save the image to a universal format.
        w32::string path = L"";
        const w32::Version version = w32::Version();
        if ( version < w32::Version::vista() ) {
            path =  __library__() + L"\\__current__.bmp";
        }
        else {
            path =  __library__() + L"\\__current__.jpg";
        }
        image.save(path);
        
            // Set it as wallpaper.
        w32::shl::wallpaper(path, style);
    }

        // Supported file extensions.
    static const w32::string __extensions__[] = {
        L"*.bmp", L"*.jpg", L"*.jpeg", L"*.png",
        //L"*.gif",
    };
    const int __extension_count__ =
        sizeof(__extensions__) / sizeof(__extensions__[0]);

        /*!
         * @brief Program initialization code.
         */
    void Startup ()
    {
            // Play nice.
        if ( __timer__ != 0 ) {
            return;
        }
        
            // Dump any existing list of wallpapers.
        __wallpapers__.clear();
        
            // Look for desktop wallpaper images.
        w32::string folder(L"");
        try {
            folder = __library__();
        }
        catch ( ... )
        {
                // Library is not set or set to invalid path.
            BrowseForLibrary();
            
                // Fetch new library path.
            folder = __library__();
        }
        
            // Cache a list of all files in the wallpaper stash.
        for ( int i = 0; (i < __extension_count__); ++i )
        {
            try {
                w32::fs::Search::Result result;
                w32::fs::Search search(folder+L"\\"+__extensions__[i], result);
                do {
                    __wallpapers__.push_back(folder + L"\\" + result.name());
                }
                while ( search.next(result) );
            }
                // Ignore if folder can't be found...
            catch ( ... )
            {
            }
        }
        
            // Never display them in the same order.
        std::random_shuffle(__wallpapers__.begin(), __wallpapers__.end());
        
            // Make sure we start receiving notifications.
        const w32::Timespan delay(5, w32::Timespan::Unit::second());
        __timer__ = new w32::gdi::Timer(delay, &Swap);
#if 0
        w32::fs::ChangeNotifications::Filter filter =
            w32::fs::ChangeNotifications::Filter::filename |
            w32::fs::ChangeNotifications::Filter::foldername;
        w32::fs::ChangeNotifications changes(folder, filter, true);
#endif
    }

        /*!
         * @brief Program cleanup code.
         */
    void Shutdown ()
    {
            // Play nice.
        if ( __timer__ == 0 ) {
            return;
        }
        
            // Make sure we don't receive any more notifications.
        delete __timer__, __timer__ = 0;
        
            // Remove all wallpapers from the list.
        __wallpapers__.clear();
    }

        /*!
         * @brief Menu callback to change the desktop wallpaper right away.
         */
    void SwapNow ()
    {
            // Change the wallpaper.
        Swap();
        
            // Make sure it stays as long as the others.
        __timer__->reset();
    }

        /*!
         * @brief Menu callback to change the desktop wallpaper library.
         */
    void BrowseForLibrary ()
    {
            // Setup browsing capababilitiees.
        static const w32::string title(L"Wallpaper Library");
        w32::shl::Browser browser; browser.title(title);
        
            // Ask the user to choose a folder.
        w32::string path = browser.prompt();
        
            // Set the path, if user actually selected something.
        if ( path.length() == 0 ) {
            return;
        }
        __library__(path);
        
            // Reload the libary.
        Shutdown(), Startup();
    }

        /*!
         * @brief Menu callback to terminate the program.
         */
    void Exit ()
    {
        ::PostQuitMessage(0);
    }

        // Dispatch table for menu.
    const Entry entries[] = {
        Entry(L"Exit", Exit),
        Entry(L"Swap Now", SwapNow),
        Entry(L"Change Library", BrowseForLibrary),
    };

}

#include <w32/app/taskbar-application.cpp>
