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

#include <w32.gdi/WindowEvents.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    WindowEvents::WindowEvents ( const Window& window )
        : myWindow(window)
    {
    }

    const Window& WindowEvents::window () const
    {
        return (myWindow);
    }

    bool WindowEvents::next ( Event& event, Filter filter )
    {
        const ::BOOL result = ::GetMessage(
            &event.data(), myWindow.handle(), filter.first(), filter.last()
            );
        if ( result == -1 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetMessage, error);
        }
        return (result != 0);
    }

    bool WindowEvents::peek ( Event& event, Filter filter )
    {
        const ::BOOL result = ::PeekMessage(
            &event.data(), myWindow.handle(),
            filter.first(), filter.last(), PM_NOREMOVE
            );
        return (result != FALSE);
    }

    void WindowEvents::post ( const Message& message )
    {
        const ::BOOL result = ::PostMessage(
            myWindow.handle(), message.wm(), message.wp(), message.lp()
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(PostMessage,::GetLastError());
        }
    }

} }
