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

#include <w32.tp/Cleanup.hpp>
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

namespace w32 { namespace tp {

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
