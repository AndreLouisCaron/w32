// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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

} }
