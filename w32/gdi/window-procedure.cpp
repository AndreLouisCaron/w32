// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/gdi/LeftButtonDown.hpp>
#include <win32c/gdi/LeftButtonUp.hpp>
#include <win32c/gdi/LeftButtonDoubleClick.hpp>
#include <win32c/gdi/RightButtonDown.hpp>
#include <win32c/gdi/LosingMouseCapture.hpp>
#include <win32c/gdi/GainedKeyboardFocus.hpp>
#include <win32c/gdi/LosingKeyboardFocus.hpp>
#include <win32c/gdi/MouseMove.hpp>
#include <win32c/gdi/MouseLeave.hpp>
#include <win32c/gdi/MouseHover.hpp>
#include <win32c/gdi/Quit.hpp>
#include <win32c/gdi/KeyPressed.hpp>
#include <win32c/gdi/KeyReleased.hpp>
#include <Windows.h>

namespace {

    ::LRESULT __stdcall WindowProcedure (
        ::HWND handle, ::UINT message, ::WPARAM wparam, ::LPARAM lparam
    )
    {
        if ( message == WM_LBUTTONDOWN ) {
            win32c::gdi::LeftButtonDown(wparam,lparam);
        }
        else if ( message == WM_LBUTTONUP ) {
            win32c::gdi::LeftButtonUp(wparam,lparam);
        }
        else if ( message == WM_LBUTTONDBLCLK ) {
            win32c::gdi::LeftButtonDoubleClick(wparam,lparam);
        }
        else if ( message == WM_RBUTTONDOWN ) {
            win32c::gdi::RightButtonDown(wparam,lparam);
        }
        else if ( message == WM_MOUSEHOVER ) {
            win32c::gdi::MouseHover(wparam,lparam);
        }
        else if ( message == WM_MOUSEMOVE ) {
            win32c::gdi::MouseMove(wparam,lparam);
        }
        else if ( message == WM_MOUSELEAVE ) {
            win32c::gdi::MouseLeave(wparam,lparam);
        }
        else if ( message == WM_CAPTURECHANGED ) {
            win32c::gdi::LosingMouseCapture(wparam,lparam);
        }
        else if ( message == WM_SETFOCUS ) {
            win32c::gdi::GainedKeyboardFocus(wparam,lparam);
        }
        else if ( message == WM_KILLFOCUS ) {
            win32c::gdi::LosingKeyboardFocus(wparam,lparam);
        }
        else if ( message == WM_KEYDOWN ) {
            win32c::gdi::KeyPressed(wparam,lparam);
        }
        else if ( message == WM_KEYUP ) {
            win32c::gdi::KeyReleased(wparam,lparam);
        }
        // We cannot receive this...
        else if ( message == WM_QUIT ) {
            win32c::gdi::Quit(wparam,lparam);
        }
        return (::DefWindowProc(handle,message,wparam,lparam));
    }

}
