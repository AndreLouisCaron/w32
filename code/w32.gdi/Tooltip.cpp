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

#include <w32.gdi/Tooltip.hpp>

namespace {

    ::HWND create ( ::HWND parent )
    {
        const ::HWND handle = ::CreateWindowExW(
            WS_EX_TOPMOST, TOOLTIPS_CLASSW, 0,
            WS_POPUP|TTS_NOPREFIX|TTS_ALWAYSTIP,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            parent, 0, ::GetModuleHandle(0), 0
            );
        if ( handle == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateWindowEx, error);
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    Tooltip::Tooltip ( const Handle& handle )
        : Control(handle)
    {
    }

    Tooltip::Tooltip ( Window& window )
        : Control(claim(::create( window.handle() )))
    {
        activate();
    }

    void Tooltip::add ( const Tool& tool )
    {
        const ::BOOL result = static_cast<::BOOL>(::SendMessageW(
            handle(), TTM_ADDTOOLA, 0,
            reinterpret_cast< ::LPARAM >(&tool.data())
            ));
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SendMessage,::GetLastError());
        }
    }

    void Tooltip::remove ( const Tool& tool )
    {
        ::SendMessageW(
            handle(), TTM_DELTOOLW, 0,
            reinterpret_cast< ::LPARAM >(&tool.data())
            );
    }

    int Tooltip::maxTipWidth ( int width )
    {
        const int result = static_cast<int>(::SendMessageW(
            handle(), TTM_SETMAXTIPWIDTH, 0, static_cast<::LPARAM>(width)
            ));
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SendMessage,::GetLastError());
        }
        return (result);
    }

    void Tooltip::activate ()
    {
        ::SendMessageW(handle(),TTM_ACTIVATE,static_cast<::WPARAM>(TRUE),0);
    }

    void Tooltip::deactivate ()
    {
        ::SendMessageW(handle(),TTM_ACTIVATE,static_cast<::WPARAM>(FALSE),0);
    }

    void Tooltip::update ()
    {
        ::SendMessageW(handle(),TTM_UPDATE,0,0);
    }

    void Tooltip::pop ()
    {
        ::SendMessageW(handle(),TTM_POP,0,0);
    }

    void Tooltip::popup ()
    {
        ::SendMessageW(handle(),TTM_POPUP,0,0);
    }

    int Tooltip::toolCount () const
    {
        const int result = static_cast<int>(::SendMessageW(
            handle(), TTM_GETTOOLCOUNT, 0, 0
            ));
        return (result);
    }

    void Tooltip::title ( const string& text )
    {
        title(text, Icon::none());
    }

    void Tooltip::title ( const string& text, const Icon& icon )
    {
        const ::BOOL result = static_cast<::BOOL>(::SendMessageW(
            handle(), TTM_SETTITLE, icon.value(),
            reinterpret_cast< ::LPARAM >(text.data()))
            );
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SendMessage, error);
        }
    }

#if (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_XPSP2)

    void Tooltip::title ( const string& text, const w32::gdi::Icon& icon )
    {
        const ::BOOL result = static_cast<::BOOL>(::SendMessageW(
            handle(), TTM_SETTITLE,
            reinterpret_cast< ::WPARAM >((::HICON)icon.handle()),
            reinterpret_cast< ::LPARAM >(text.data()))
            );
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SendMessage, error);
        }
    }

#endif /* (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_XPSP2) */

    const Tooltip::Icon Tooltip::Icon::errorLarge ()
    {
        return (TTI_ERROR_LARGE);
    }

    Tooltip::Tool::Tool ( const Window& window )
        : myCaption("")
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.cbSize = sizeof(myData);
        myData.uFlags = TTF_SUBCLASS;
        myData.hwnd = window.handle();
        myData.hinst = ::GetModuleHandle(0);
        ::GetClientRect(window.handle(), &myData.rect);
    }

    Tooltip::Tool::Tool ( const Tool& other )
        : myData(other.myData), myCaption(other.myCaption)
    {
        myData.lpszText = const_cast<char*>(myCaption.data());
    }

    Tooltip::Tool::Data& Tooltip::Tool::data ()
    {
        return (myData);
    }

    const Tooltip::Tool::Data& Tooltip::Tool::data () const
    {
        return (myData);
    }

    void Tooltip::Tool::caption ( const string& text )
    {
        myCaption = text;
        myData.lpszText = const_cast<char*>(myCaption.data());
    }

    void Tooltip::Tool::area ( const Rectangle& bounds )
    {
        myData.rect = bounds.data();
    }

    Tooltip::Tool& Tooltip::Tool::operator= ( const Tool& other )
    {
        myData = other.myData;
        myCaption = other.myCaption;
        myData.lpszText = const_cast<char*>(myCaption.data());
        return (*this);
    }

    const Tooltip::Icon Tooltip::Icon::none ()
    {
        return (TTI_NONE);
    }

    const Tooltip::Icon Tooltip::Icon::info ()
    {
        return (TTI_INFO);
    }

    const Tooltip::Icon Tooltip::Icon::warning ()
    {
        return (TTI_WARNING);
    }

    const Tooltip::Icon Tooltip::Icon::error ()
    {
        return (TTI_ERROR);
    }

    const Tooltip::Icon Tooltip::Icon::infoLarge ()
    {
        return (TTI_INFO_LARGE);
    }

    const Tooltip::Icon Tooltip::Icon::warningLarge ()
    {
        return (TTI_WARNING_LARGE);
    }

    Tooltip::Icon::Icon ( Value value )
        : myValue(value)
    {
    }

    Tooltip::Icon::Value Tooltip::Icon::value () const
    {
        return (myValue);
    }

} }
