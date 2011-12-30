// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.tp/Work.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace tp {

    ::PTP_WORK Work::setup ( ::PTP_CALLBACK_ENVIRON queue,
                             ::PTP_WORK_CALLBACK callback, void * context )
    {
        const ::PTP_WORK handle  =
            ::CreateThreadpoolWork(callback, context, queue);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThreadpoolTimer, error);
        }
        return (handle);
    }

    Work::~Work ()
    {
        ::CloseThreadpoolWork(myHandle);
    }

    void Work::submit ()
    {
        ::SubmitThreadpoolWork(myHandle);
    }

    void Work::wait ( bool cancel_pending )
    {
        ::WaitForThreadpoolWorkCallbacks(
            myHandle, cancel_pending?TRUE:FALSE);
    }

} }
