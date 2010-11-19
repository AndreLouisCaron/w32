// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mt/Cleanup.hpp>
#include <w32/Error.hpp>

namespace {

    ::PTP_CLEANUP_GROUP allocate ()
    {
        const ::PTP_CLEANUP_GROUP handle = ::CreateThreadpoolCleanupGroup();
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThreadpoolCleanupGroup, error);
        }
        return (handle);
    }

    void abandon ( ::PTP_CLEANUP_GROUP object ) {}
    void destroy ( ::PTP_CLEANUP_GROUP object )
    {
        ::CloseThreadpoolCleanupGroup(object);
    }

}

namespace w32 { namespace mt {

    const Cleanup::Handle Cleanup::claim ( ::PTP_CLEANUP_GROUP handle )
    {
        return (Handle(handle, &::destroy));
    }

    const Cleanup::Handle Cleanup::proxy ( ::PTP_CLEANUP_GROUP handle )
    {
        return (Handle(handle, &::abandon));
    }

    Cleanup::Cleanup ()
        : myHandle(claim(::allocate()))
    {
    }

    const Cleanup::Handle& Cleanup::handle () const
    {
        return (myHandle);
    }

    void Cleanup::close ( bool cancel, void * context )
    {
        ::CloseThreadpoolCleanupGroupMembers
            (handle(), cancel?TRUE:FALSE, context);
    }

} }
