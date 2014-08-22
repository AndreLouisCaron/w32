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

#include <w32.mt/AutoResetEvent.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( const wchar_t * name )
    {
        const ::HANDLE handle = ::CreateEventW(0, FALSE, 0, name);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateEvent, error);
        }
        return (handle);
    }

    ::HANDLE find ( const wchar_t * name )
    {
        const ::HANDLE handle = ::CreateEventW(0, FALSE, 0, name);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateEvent, error);
        }
        return (handle);
    }

}

namespace w32 { namespace mt {

    AutoResetEvent AutoResetEvent::open ( const string& name )
    {
        const Handle handle(Object::claim(::find(name.c_str())));
        return (AutoResetEvent(handle));
    }

    AutoResetEvent::AutoResetEvent ( const Handle& handle )
        : Object(handle)
    {
    }

    AutoResetEvent::AutoResetEvent ()
        : Object(Object::claim(::allocate(0)))
    {
    }

    AutoResetEvent::AutoResetEvent ( const string& name )
        : Object(Object::claim(::allocate(name.data())))
    {
    }

    void AutoResetEvent::set ()
    {
        const ::BOOL result = ::SetEvent(handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetEvent, error);
        }
    }

    void AutoResetEvent::wait ()
    {
        return (Waitable(*this).wait());
    }

    bool AutoResetEvent::wait (w32::Timespan timeout)
    {
        return (Waitable(*this).wait(timeout));
    }

    bool AutoResetEvent::test ()
    {
        return (wait(w32::Timespan(0)));
    }

    AutoResetEvent::operator Waitable () const
    {
        return Waitable(handle());
    }

} }
