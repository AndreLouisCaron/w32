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

#include <w32.gdi/Timer.hpp>
#include <w32/Error.hpp>

namespace {

    ::UINT_PTR set (
        ::HWND window, ::UINT_PTR handle, ::UINT timeout, ::TIMERPROC callback )
    {
        handle = ::SetTimer(window, handle, timeout, callback);
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetTimer, ::GetLastError());
        }
        return (handle);
    }

    ::UINT_PTR acquire ( ::HWND window, ::UINT timeout, ::TIMERPROC callback )
    {
        return (set(window, 0, timeout, callback));
    }

    void release ( ::HWND window, ::UINT_PTR handle )
    {
        const ::BOOL result = ::KillTimer(window, handle);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace gdi {

    Timer::Timer ( Timespan timeout, Callback callback )
        : myWindow(0), myTimeout(timeout), myCallback(callback),
          myHandle(::acquire(myWindow, myTimeout.ticks(), myCallback))
    {
    }

    Timer::Timer ( const Window& window, Timespan timeout, Callback callback )
        : myWindow(window.handle()), myTimeout(timeout), myCallback(callback),
          myHandle(::acquire(myWindow, myTimeout.ticks(), myCallback))
    {
    }

    Timer::~Timer ()
    {
        ::release(myWindow, myHandle);
    }

    Timer::Handle Timer::handle () const
    {
        return (myHandle);
    }

    Timespan Timer::timeout () const
    {
        return (myTimeout);
    }

    void Timer::timeout ( Timespan timeout )
    {
        myTimeout = timeout;
        reset(myTimeout, myCallback);
    }

    Timer::Callback Timer::callback () const
    {
        return (myCallback);
    }

    void Timer::callback ( Callback callback )
    {
        myCallback = callback;
        reset(myTimeout, myCallback);
    }

    void Timer::reset ()
    {
        reset(myTimeout, myCallback);
    }

    void Timer::reset ( Timespan timeout, Callback callback)
    {
        myTimeout = timeout;
        myCallback = callback;
        ::set(myWindow, myHandle, myTimeout.ticks(), myCallback);
    }

} }
