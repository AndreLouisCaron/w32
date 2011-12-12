// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
