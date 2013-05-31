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

#include <w32.ipc/Job.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE create ( ::LPCWSTR name )
    {
        const ::HANDLE result = ::CreateJobObjectW(0, name);
        if ( result == NULL ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateJobObject, error);
        }
        return (result);
    }

    ::HANDLE find ( ::LPCWSTR name )
    {
        const ::HANDLE result = ::OpenJobObjectW(
                                    JOB_OBJECT_ALL_ACCESS , FALSE, name
                                );
        if ( result == NULL ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(OpenJobObject, error);
        }
        return (result);
    }

}

namespace w32 { namespace ipc {

    Job Job::open ( const string& name )
    {
        const Handle handle(Object::claim(::find(name.c_str())));
        return (Job(handle));
    }

    Job::Job ( const Handle& handle )
        : Object(handle)
    {
    }

    Job::Job ()
        : Object(Object::claim(::create(0)))
    {
    }

    Job::Job ( const string& name )
        : Object(Object::claim(::create(name.c_str())))
    {
    }

    void Job::add ( Process& process )
    {
        const ::BOOL result = ::AssignProcessToJobObject(
            handle(), process.handle()
            );
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(AssignProcessToJobObject, error);
        }
    }

    bool Job::contains ( const Process& process )
    {
        ::BOOL contains = FALSE;
        const ::BOOL result = ::IsProcessInJob(
            handle(), process.handle(), &contains
            );
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(IsProcessInJob, error);
        }
        return (contains != FALSE);
    }

    void Job::terminate ( uint status )
    {
        const ::BOOL result = ::TerminateJobObject(
            handle(), status
            );
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TerminatJobObject, error);
        }
    }

    Job::operator Waitable () const
    {
        return (Waitable(handle()));
    }

} }
