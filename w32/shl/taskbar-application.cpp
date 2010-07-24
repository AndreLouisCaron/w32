// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/taskbar-application.hpp>
#include <w32.dbg.hpp>
#include <exception>

namespace {

    w32::gdi::Point cursor ()
    {
        ::POINT position = { 0 };
        if ( ::GetCursorPos(&position) == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetCursorPos,::GetLastError());
        }
        return (w32::gdi::Point(position));
    }

    const ::UINT TaskbarNotification = WM_APP + 1;
    ::UINT TaskbarCreated = 0;

    w32::shl::TaskbarIcon * __icon__ = 0;

    ::LRESULT __stdcall WindowProcedure (
        ::HWND window, ::UINT message, ::WPARAM wparam, ::LPARAM lparam
        )
    {
        if ( message == WM_CREATE )
        {
            try {
                TaskbarCreated = w32::shl::TaskbarIcon::creation();
                
                w32::gdi::Window w(w32::gdi::Window::proxy(window));
                __icon__ = new w32::shl::TaskbarIcon(w, 100);
                __icon__->message(TaskbarNotification);
                __icon__->image(w.smallicon());
                __icon__->tooltip("Wallpaper Swapper");
            }
            catch ( const w32::Error& error )
            {
                w32::gdi::messagebox("Debug!", error.what());
                return (1);
            }
            catch ( const std::bad_alloc& error )
            {
                w32::gdi::messagebox("Debug!", error.what());
                return (1);
            }
            
                // Tell the shell we want to display the icon.
            w32::shl::TaskbarIcon::add(*__icon__);
        }
        else if ( message == TaskbarCreated )
        {
                // Tell the shell we still want to display the icon.
            w32::shl::TaskbarIcon::add(*__icon__);
        }
        else if ( message == TaskbarNotification )
        {
                // Locate the taskbar icon identifier.
            const ::UINT identifier = static_cast<::UINT>(wparam);
            
                // Locate the mouse message that occured event.
            const ::UINT event = static_cast<::UINT>(lparam);
            
                // React based on mouse message.
            switch ( event )
            {
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_LBUTTONDBLCLK:
            {
                w32::gdi::Menu menu;
                
                    // Populate the menu.
                const int count = sizeof(entries) / sizeof(Entry);
                for ( int i = 0; (i < count); ++i ) {
                    menu.insert(entries[i].first, 0, i+1);
                }
                
                     // Show it.
                ::SetForegroundWindow(window);
                
                w32::gdi::Window w(w32::gdi::Window::proxy(window));
                const ::BOOL result = menu.popup(w, cursor());
                
                    // Handle the message.
                if ((result > 0) && (result <= count))
                {
                    try
                    {
                    w32::dbg::StructuredException::FilterReplacement filter;
                         
                        (*entries[result-1].second)();
                    }
                    catch ( const w32::Error& error ) {
                        w32::gdi::messagebox("debug!", error.what());
                    }
                    catch ( const w32::dbg::StructuredException& error ) {
                        w32::gdi::messagebox("debug!", error.what());
                    }
                    catch ( const std::exception& error ) {
                        w32::gdi::messagebox("debug!", error.what());
                    }
                }
                ::SendMessage(window, WM_NULL, 0, 0);
            } break;
            
            case WM_MOUSEHOVER:
            case WM_MOUSEMOVE:
            default: {
                } break;
            }
        }
        else if ( message == WM_DESTROY )
        {
                // Tell the shell we want to destroy the icon.
            w32::shl::TaskbarIcon::remove(*__icon__);
        }
        
        return (::DefWindowProc(window, message, wparam, lparam));
    }

    using namespace w32;
    using namespace w32::gdi;
    using w32::gdi::Rectangle;

    class MyApplication :
        public Application< MyApplication >
    {
        /* construction. */
    public:
        MyApplication ( Registration& registration )
            : Application< MyApplication >(registration, *this)
        {
            Startup();
        }

        ~MyApplication ()
        {
            Shutdown();
        }

        /* methods. */
    public:
    };

}

#include <w32/gdi/windows-program.hpp>

namespace {

    int run ( const w32::string& command, int )
    {
            // Create an application window.
        w32::gdi::Icon icon("wallpaper-swapper.ico");
        w32::gdi::Class description(L"wallpaper-swapper");
        description.smallIcon(icon);
        description.eventProcedure(&::WindowProcedure);
        w32::gdi::Registration registration(description);
        ::MyApplication _(registration);
        
            // Wait until doomsday!
        return (w32::gdi::loop());
    }

}

#include <w32/gdi/windows-program.cpp>
