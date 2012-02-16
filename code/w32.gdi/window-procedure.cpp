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

#include <w32.gdi/LeftButtonDown.hpp>
#include <w32.gdi/LeftButtonUp.hpp>
#include <w32.gdi/LeftButtonDoubleClick.hpp>
#include <w32.gdi/RightButtonDown.hpp>
#include <w32.gdi/LosingMouseCapture.hpp>
#include <w32.gdi/GainedKeyboardFocus.hpp>
#include <w32.gdi/LosingKeyboardFocus.hpp>
#include <w32.gdi/MouseMove.hpp>
#include <w32.gdi/MouseLeave.hpp>
#include <w32.gdi/MouseHover.hpp>
#include <w32.gdi/Quit.hpp>
#include <w32.gdi/KeyPressed.hpp>
#include <w32.gdi/KeyReleased.hpp>
#include <Windows.h>

namespace {

    ::LRESULT __stdcall WindowProcedure (
        ::HWND handle, ::UINT message, ::WPARAM wparam, ::LPARAM lparam
    )
    {
        if ( message == WM_LBUTTONDOWN ) {
            w32::gdi::LeftButtonDown(wparam,lparam);
        }
        else if ( message == WM_LBUTTONUP ) {
            w32::gdi::LeftButtonUp(wparam,lparam);
        }
        else if ( message == WM_LBUTTONDBLCLK ) {
            w32::gdi::LeftButtonDoubleClick(wparam,lparam);
        }
        else if ( message == WM_RBUTTONDOWN ) {
            w32::gdi::RightButtonDown(wparam,lparam);
        }
        else if ( message == WM_MOUSEHOVER ) {
            w32::gdi::MouseHover(wparam,lparam);
        }
        else if ( message == WM_MOUSEMOVE ) {
            w32::gdi::MouseMove(wparam,lparam);
        }
        else if ( message == WM_MOUSELEAVE ) {
            w32::gdi::MouseLeave(wparam,lparam);
        }
        else if ( message == WM_CAPTURECHANGED ) {
            w32::gdi::LosingMouseCapture(wparam,lparam);
        }
        else if ( message == WM_SETFOCUS ) {
            w32::gdi::GainedKeyboardFocus(wparam,lparam);
        }
        else if ( message == WM_KILLFOCUS ) {
            w32::gdi::LosingKeyboardFocus(wparam,lparam);
        }
        else if ( message == WM_KEYDOWN ) {
            w32::gdi::KeyPressed(wparam,lparam);
        }
        else if ( message == WM_KEYUP ) {
            w32::gdi::KeyReleased(wparam,lparam);
        }
        // We cannot receive this...
        else if ( message == WM_QUIT ) {
            w32::gdi::Quit(wparam,lparam);
        }
        return (::DefWindowProc(handle,message,wparam,lparam));
    }

}
