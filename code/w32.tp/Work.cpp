// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.tp/Work.hpp>
#include <w32/Error.hpp>

namespace {

    void abandon ( ::PTP_WORK object ) {}
    void destroy ( ::PTP_WORK object )
    {
        ::CloseThreadpoolWork(object);
    }

}

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

    Work::Handle Work::claim ( ::PTP_WORK object )
    {
        return (Handle(object, &::destroy));
    }

    Work::Handle Work::proxy ( ::PTP_WORK object )
    {
        return (Handle(object, &::abandon));
    }

    Work::Work ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Work::Handle& Work::handle () const
    {
        return (myHandle);
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
