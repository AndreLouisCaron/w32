// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mt/Queue.hpp>
#include <w32/mt/Cleanup.hpp>
#include <w32/mt/Pool.hpp>
#include <w32/Error.hpp>
#include <w32/fs/Time.hpp>

namespace w32 { namespace mt {

    Queue::Queue ()
    {
        ::InitializeThreadpoolEnvironment(&myData);
    }

    Queue::~Queue ()
    {
        ::DestroyThreadpoolEnvironment(&myData);
    }

    void Queue::pool ( Pool& pool )
    {
        ::SetThreadpoolCallbackPool(&myData, pool.handle());
    }

    void Queue::submit ( Work work, void * context )
    {
            // Create the work item.
        const ::PTP_WORK result =
            ::CreateThreadpoolWork(work, context, &myData);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThreadpoolWork, error);
        }
        
            // Submit it.
        ::SubmitThreadpoolWork(result);
    }

    void Queue::submit ( Timer work, const Timespan& delai, void * context )
    {
            // Create the work item.
        const ::PTP_TIMER result =
            ::CreateThreadpoolTimer(work, context, &myData);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThreadpoolTimer, error);
        }
        
            // Submit it.
        ::ULARGE_INTEGER duetime; ::FILETIME deadline;
        duetime.QuadPart = -int64(delai.ticks()*10000);
        deadline.dwLowDateTime = duetime.LowPart;
        deadline.dwHighDateTime = duetime.HighPart;
        ::SetThreadpoolTimer(result, &deadline, 0, 0);
    }

    void Queue::cleanup ( Cleanup& cleanup, Cancel cancel )
    {
        ::SetThreadpoolCallbackCleanupGroup
            (&myData, cleanup.handle(), cancel);
    }

} }
