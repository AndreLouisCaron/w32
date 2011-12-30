// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.tp/Pool.hpp>
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

namespace w32 { namespace tp {

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

    Pool::Pool ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Pool::Handle& Pool::handle () const
    {
        return (myHandle);
    }

    void Pool::minimum_threads ( dword minimum )
    {
        ::SetThreadpoolThreadMinimum(handle(), minimum);
    }

    void Pool::maximum_threads ( dword maximum )
    {
        ::SetThreadpoolThreadMaximum(handle(), maximum);
    }

    void Pool::threads ( dword count )
    {
        threads(count, count);
    }

    void Pool::threads ( dword minimum, dword maximum )
    {
        minimum_threads(minimum);
        maximum_threads(maximum);
    }

} }
