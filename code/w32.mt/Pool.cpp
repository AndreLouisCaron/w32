// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mt/Pool.hpp>
#include <w32/Error.hpp>

namespace {

    ::PTP_POOL allocate ()
    {
        const ::PTP_POOL handle = ::CreateThreadpool(0);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThreadpool, error);
        }
        return (handle);
    }

    void abandon ( ::PTP_POOL object ) {}
    void destroy ( ::PTP_POOL object )
    {
        ::CloseThreadpool(object);
    }

}

namespace w32 { namespace mt {

    const Pool::Handle Pool::claim ( ::PTP_POOL handle )
    {
        return (Handle(handle, &::destroy));
    }

    const Pool::Handle Pool::proxy ( ::PTP_POOL handle )
    {
        return (Handle(handle, &::abandon));
    }

    Pool::Pool ()
        : myHandle(claim(::allocate()))
    {
    }

    const Pool::Handle& Pool::handle () const
    {
        return (myHandle);
    }

    void Pool::threads ( dword count )
    {
        threads(count, count);
    }

    void Pool::threads ( dword minimum, dword maximum )
    {
        ::SetThreadpoolThreadMinimum(handle(), minimum);
        ::SetThreadpoolThreadMaximum(handle(), maximum);
    }

} }
