#ifndef _w32_tp_Hints_hpp__
#define _w32_tp_Hints_hpp__

#include "__configure__.hpp"

namespace w32 { namespace tp {

    class Hints
    {
    private:
        ::PTP_CALLBACK_INSTANCE myHandle;

    public:
        explicit Hints ( ::PTP_CALLBACK_INSTANCE handle )
            : myHandle(handle)
        {
        }

        // returns true when the thread pool has other threads and/or when the
        // thread pool was able to spawn an extra thread to free up this one.
        // if it returns false, the thread pool may lose efficiency.
        bool may_run_long ()
        {
            return (::CallbackMayRunLong(myHandle) != FALSE);
        }

        void signal_on_return ( ::HANDLE event )
        {
            ::SetEventWhenCallbackReturns(myHandle, event);
        }

        void leave_on_return ( ::CRITICAL_SECTION& section )
        {
            ::LeaveCriticalSectionWhenCallbackReturns(myHandle, &section);
        }

        void release_on_return ( ::HANDLE mutex )
        {
            ::ReleaseMutexWhenCallbackReturns(myHandle, mutex);
        }

        void release_on_return ( ::HANDLE semaphore, ::DWORD count )
        {
            ::ReleaseSemaphoreWhenCallbackReturns(myHandle, semaphore, count);
        }

        void release_on_return ( ::HMODULE library )
        {
            ::FreeLibraryWhenCallbackReturns(myHandle, library);
        }

        // unblock pending wait operations on the Work/Wait/Timer/IO callback
        // item that requested this callback execution.  the documentation is
        // unclear on why you would want to use this...
        void break_off ()
        {
            ::DisassociateCurrentThreadFromCallback(myHandle);
        }
    };

} }

#endif /* _w32_tp_Hints_hpp__ */
