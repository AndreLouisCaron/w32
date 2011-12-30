// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.tp/Transfer.hpp>
#include <w32/Error.hpp>

namespace {

    void abandon ( ::PTP_IO object ) {}
    void destroy ( ::PTP_IO object )
    {
        ::CloseThreadpoolIo(object);
    }

}

namespace w32 { namespace tp {

    ::PTP_IO Transfer::setup ( ::PTP_CALLBACK_ENVIRON queue, ::HANDLE stream,
                               ::PTP_WIN32_IO_CALLBACK callback, void * context )
    {
        const ::PTP_IO handle =
            ::CreateThreadpoolIo(stream, callback, context, queue);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThreadpoolIo, error);
        }
        ::StartThreadpoolIo(handle);
        return (handle);
    }

    Transfer::Handle Transfer::claim ( ::PTP_IO object )
    {
        return (Handle(object, &::destroy));
    }

    Transfer::Handle Transfer::proxy ( ::PTP_IO object )
    {
        return (Handle(object, &::abandon));
    }

    Transfer::Transfer ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Transfer::Handle& Transfer::handle () const
    {
        return (myHandle);
    }

    void Transfer::cancel ()
    {
        ::CancelThreadpoolIo(myHandle);
    }

    void Transfer::wait ( bool cancel_pending )
    {
        ::WaitForThreadpoolIoCallbacks
            (myHandle, cancel_pending?TRUE:FALSE);
    }

} }
