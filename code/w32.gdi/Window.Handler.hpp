#ifndef _w32_gdi_WindowHandler_hpp__
#define _w32_gdi_WindowHandler_hpp__

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
#include <w32.gdi/MessageBox.hpp>
#include <w32.gdi/Message.hpp>
#include <w32.gdi/PaintContext.hpp>
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

    template<typename T>
    class Window::Handler
    {
    public:
            /*!
             * @brief Called to signal intention to close.
             *
             * This is the hook to override if you wish to pop a dialog box
             * asking the user to save changes before exiting your application.
             *
             * @return @c true to accept the request, false to ignore.
             */
        bool close () { return (true); }

        bool command () { return (false); }
        bool notify ( Window& target, ::LPNMHDR context ) { return (false); }
        bool paint () { return (false); }
        void hotkey ( int identifier, uint modifiers, uint key ) {}
        bool character ( wchar_t value, dword flags ) { return (false); }
        bool keyup ( uint code ) { return (false); }
        bool keyup ( uint code, dword flags ) { return (keyup(code)); }
        bool syskeyup ( uint code ) { return (false); }
        bool syskeyup ( uint code, dword flags ) { return (syskeyup(code)); }

#if 0
        void moving () {}
        void moved () {}
        void resizing () {}
        void resized () {}
        void destroy () {}
#endif
    };

        // Long and painful dispatcher...
    template<typename T>
    ::LRESULT __stdcall Window::adapt
        ( ::HWND hwnd, uint message, wparam wp, lparam lp )
    {
        Window window(Window::proxy(hwnd));
        T *const handler =
            reinterpret_cast< T* >(window.extra());
        
            // Alt-F4 or red X were pressed.
        if ( message == WM_CLOSE )
        {
            if ( handler->close() ) {
                window.hide();
            }
                // *Never* call DefWindowProc(), it would destroy our window!
            return (0);
        }
            // Common control notifications, == WM_COMMAND with info!
        else if ( message == WM_NOTIFY )
        {
                // Extract actual notification information.
            const ::NMHDR *const header =
                reinterpret_cast< const ::NMHDR* >(lp);
            Window child(Window::proxy(header->hwndFrom));
            
            if ( handler->notify(child, header) )
            {
                    // Support message-specific return codes?
                return (0);
            }
        }
            // Child control notifications, menu and accelerator commands.
        else if ( message == WM_COMMAND )
        {
                // Control?
            if ( lp != 0 )
            {
                const ::UINT code = HIWORD(wp);
                Window child(Window::proxy(reinterpret_cast< ::HWND >(lp)));
                
                if ( handler->command(child, code) ) {
                    return (0);
                }
            }
                // Menu?
            else if ( HIWORD(wp) == 0 )
            {
                const ::WORD menu = LOWORD(wp);
            }
                // Accelerator?
            else if ( HIWORD(wp) == 1 )
            {
                const ::WORD accelerator = LOWORD(wp);
            }
                // Failure?
            else {}
        }
        else if ( message == WM_NOTIFYFORMAT ) {
            return (NFR_UNICODE);
        }
        else if ( message == WM_PAINT )
        {
            std::cerr << "Painting!" << std::endl;
            if ( handler->paint() ) { return (0); }
        }
        else if ( message == WM_CHAR )
        {
            if ( handler->character(wp, lp) ) { return (0); }
        }
        else if ( message == WM_HOTKEY )
        {
            handler->hotkey(wp, LOWORD(lp), HIWORD(lp));
        }
        else if ( message == WM_KEYUP )
        {
            if ( handler->keyup(wp, lp) ) { return (0); }
        }
        else if ( message == WM_SYSKEYUP )
        {
            if ( handler->syskeyup(wp, lp) ) { return (0); }
        }
        
            // Always accept default behaviour.
        return (::DefWindowProcW(hwnd, message, wp, lp));
    }

} }

#endif /* _w32_gdi_WindowHandler_hpp__ */
