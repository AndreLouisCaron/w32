// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.tp/Timer.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace tp {

    ::PTP_TIMER Timer::setup ( ::PTP_CALLBACK_ENVIRON queue,
                               ::PTP_TIMER_CALLBACK callback, void * context )
    {
        const ::PTP_TIMER handle =
            ::CreateThreadpoolTimer(callback, context, queue);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThreadpoolTimer, error);
        }
        return (handle);
    }

    Timer::~Timer ()
    {
        ::CloseThreadpoolTimer(myHandle);
    }

    void Timer::start ( ::DWORD delai, ::DWORD period )
    {
        ::ULARGE_INTEGER duetime; ::FILETIME deadline;
        duetime.QuadPart = -int64(delai*10000);
        deadline.dwLowDateTime = duetime.LowPart;
        deadline.dwHighDateTime = duetime.HighPart;
        ::SetThreadpoolTimer(myHandle, &deadline, period, 0);
    }

    void Timer::cancel ()
    {
        ::SetThreadpoolTimer(myHandle, 0, 0, 0);
    }

    void Timer::wait ( bool cancel_pending )
    {
        ::WaitForThreadpoolTimerCallbacks(
            myHandle, cancel_pending?TRUE:FALSE);
    }

} }
