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

#include <w32.gdi/Static.hpp>
#include <w32.gdi/Bitmap.hpp>
#include <w32.gdi/Icon.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, L"Static", 0, standard,
            bounds.left, bounds.top, bounds.right-bounds.left,
            bounds.bottom-bounds.top, parent, 0, ::GetModuleHandle(0), 0
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateWindowEx, error);
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    Static::Static ( const Handle& handle )
        : Control(handle)
    {
    }

    Static::Static ( const Rectangle& bounds )
        : Control(claim(::create(0, 0, 0, bounds.data())))
    {
    }

    Static::Static ( Window& window, const Rectangle& bounds )
        : Control(claim(
            ::create(0, WS_CHILD, window.handle(), bounds.data())
            ))
    {
    }

    void Static::text ( const string& text )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= SS_BITMAP;
        style &= SS_ICON;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::BOOL result =::SetWindowTextW(handle(), text.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetWindowText, error);
        }
    }

    string Static::text () const
    {
            // Find out exactly how much text this contains...
        const int length = ::GetWindowTextLengthW(handle());
        
            // Allocate memory.
        string text(length);
        
            // *Finally* fetch the associated text.
        const ::BOOL result =::GetWindowTextW
            (handle(), text.data(), text.size());
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetWindowText, error);
        }
        return (text);
    }

    void Static::bitmap ( const Bitmap& bitmap )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= SS_ICON;
        style |= SS_BITMAP;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::HBITMAP image = bitmap.handle();
        ::SendMessage(
            handle(), STM_SETIMAGE, ::WPARAM(IMAGE_BITMAP), ::LPARAM(image)
            );
    }

    Bitmap Static::bitmap () const
    {
            // Query the bitmap handle.
        const ::LRESULT result = ::SendMessage(
            handle(), STM_GETIMAGE, ::WPARAM(IMAGE_BITMAP), 0
            );
        return (Bitmap(Bitmap::proxy(reinterpret_cast< ::HBITMAP >(result))));
    }

    void Static::icon ( const Icon& icon )
    {
            // Make sure the control has the appropriate style.
        ::LONG style = ::GetWindowLong(handle(), GWL_STYLE);
        style &= SS_BITMAP;
        style |= SS_ICON;
        ::SetWindowLong(handle(), GWL_STYLE, style);
        
        const ::HICON image = icon.handle();
        ::SendMessage(
            handle(), STM_SETIMAGE, ::WPARAM(IMAGE_ICON), ::LPARAM(image)
            );
    }

    Icon Static::icon () const
    {
        const ::LRESULT result = ::SendMessage(
            handle(), STM_GETIMAGE, ::WPARAM(IMAGE_ICON), 0
            );
        return (Icon(Icon::proxy(reinterpret_cast< ::HICON >(result))));
    }

} }
