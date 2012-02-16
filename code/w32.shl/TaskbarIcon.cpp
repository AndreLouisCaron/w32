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

#include <w32.shl/TaskbarIcon.hpp>
#include <strsafe.h>

namespace w32 { namespace shl {

    TaskbarIcon::Message TaskbarIcon::creation ()
    {
        const ::UINT result = ::RegisterWindowMessageA("TaskbarCreated");
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(RegisterWindowMessage, ::GetLastError());
        }
        return (result);
    }

    TaskbarIcon::TaskbarIcon ( const Window& window, Identifier identifier )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.cbSize = sizeof(myData);
        myData.hWnd = window.handle();
        myData.uID = identifier;
    }

    TaskbarIcon::Data& TaskbarIcon::data ()
    {
        return (myData);
    }

    const TaskbarIcon::Data& TaskbarIcon::data () const
    {
        return (myData);
    }

    void TaskbarIcon::message ( Message value )
    {
        myData.uCallbackMessage = value;
        myData.uFlags |= NIF_MESSAGE;
    }

    void TaskbarIcon::tooltip ( const char * text )
    {
        ::StringCbCopyN(
            myData.szTip, sizeof(myData.szTip), text, sizeof(myData.szTip)
            );
        myData.uFlags |= NIF_TIP;
    }

    void TaskbarIcon::image ( const Image& image )
    {
        myData.hIcon = image.handle();
        myData.uFlags |= NIF_ICON;
    }

    void TaskbarIcon::add ( TaskbarIcon& icon )
    {
        if ( ::Shell_NotifyIconA(NIM_ADD, &icon.data()) == 0 ) {
            UNCHECKED_WIN32C_ERROR(Shell_NotifyIcon, 0);
        }
    }

    void TaskbarIcon::remove ( TaskbarIcon& icon )
    {
        const ::BOOL result = ::Shell_NotifyIconA(NIM_DELETE, &icon.data());
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(Shell_NotifyIcon, 0);
        }
    }

} }
