// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
