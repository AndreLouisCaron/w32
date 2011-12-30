// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.tp/Wait.hpp>
#include <w32/Error.hpp>

namespace {

    void abandon ( ::PTP_WAIT object ) {}
    void destroy ( ::PTP_WAIT object )
    {
        ::CloseThreadpoolWait(object);
    }

}

namespace w32 { namespace tp {

    ::PTP_WAIT Wait::setup ( ::PTP_CALLBACK_ENVIRON queue, ::HANDLE waitable,
                             ::PTP_WAIT_CALLBACK function, void * context )
    {
        const ::PTP_WAIT handle =
            ::CreateThreadpoolWait(function, context, queue);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThreadpoolWait, error);
        }
        return (handle);
    }

    Wait::Handle Wait::claim ( ::PTP_WAIT object )
    {
        return (Handle(object, &::destroy));
    }

    Wait::Handle Wait::proxy ( ::PTP_WAIT object )
    {
        return (Handle(object, &::abandon));
    }

    Wait::Wait ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Wait::Handle& Wait::handle () const
    {
        return (myHandle);
    }

    void Wait::watch ( ::HANDLE waitable )
    {
        ::SetThreadpoolWait(myHandle, waitable, 0);
    }

    void Wait::clear ()
    {
        ::SetThreadpoolWait(myHandle, 0, 0);
    }

    void Wait::wait ( bool cancel_pending )
    {
        ::WaitForThreadpoolWaitCallbacks(
            myHandle, cancel_pending?TRUE:FALSE);
    }

} }
