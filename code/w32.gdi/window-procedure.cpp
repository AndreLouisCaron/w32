// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
