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

#include "Timer.hpp"
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( ::LPCWSTR name, ::BOOL manual )
    {
        const ::HANDLE result = ::CreateWaitableTimerW(0, manual, name);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateWaitableTimer, error);
        }
        return (result);
    }

    ::HANDLE open ( ::LPCWSTR name )
    {
        const ::HANDLE result = ::OpenWaitableTimerW
            (TIMER_ALL_ACCESS, FALSE, name);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(OpenWaitableTimer, error);
        }
        return (result);
    }

}

namespace w32 { namespace mt {

    Timer Timer::open ( const string& name )
    {
        return (Timer(claim(::open(name.data()))));
    }

    Timer::Timer ( const Handle& handle )
        : Object(handle)
    {
    }

    Timer::Timer ( bool manual )
        : Object(::allocate(0, manual?TRUE:FALSE))
    {
    }

    Timer::Timer ( const string& name, bool manual )
        : Object(::allocate(name.data(), manual?TRUE:FALSE))
    {
    }

    void Timer::wait () const
    {
        return (Waitable(handle()).wait());
    }

    bool Timer::elapsed () const
    {
        return (Waitable(handle()).test());
    }

    bool Timer::elapsed ( const Timespan& timeout ) const
    {
        return (Waitable(handle()).wait(timeout));
    }

    void Timer::invalidate ()
    {
        const ::BOOL result = ::CancelWaitableTimer(handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(OpenWaitableTimer, error);
        }
    }

    void Timer::set ( const fs::Time& expiry, long period )
    {
        ::LARGE_INTEGER data;
        data.u.HighPart = expiry.high();
        data.u.LowPart = expiry.low();
        const ::BOOL result = ::SetWaitableTimer
            (handle(), &data, period, 0, 0, FALSE);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetWaitableTimer, error);
        }
    }

    Timer::operator Waitable () const
    {
        return (Waitable(handle()));
    }

} }
