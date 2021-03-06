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

    ::PTP_WAIT Wait::setup ( ::PTP_CALLBACK_ENVIRON queue,
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
