// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
