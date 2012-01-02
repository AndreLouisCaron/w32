// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/NamedPipe.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief Pseudo-socket with a UNC name used for inter-process control.
 */

#include <w32.io/NamedPipe.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE create ( ::LPCWSTR name, ::DWORD size, bool async )
    {
        const ::DWORD flags =
            PIPE_ACCESS_DUPLEX |
            (async? FILE_FLAG_OVERLAPPED : 0);
        const ::DWORD mode =
            PIPE_TYPE_BYTE            |
            PIPE_WAIT                 |
            PIPE_REJECT_REMOTE_CLIENTS;
        const ::HANDLE handle = ::CreateNamedPipeW(
            name, flags, mode, 1, size, size, 0, 0);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateNamedPipe, error);
        }
        return (handle);
    }

    ::HANDLE open ( ::LPCWSTR name, bool async )
    {
        const ::DWORD flags = async? FILE_FLAG_OVERLAPPED : 0;
        const ::HANDLE handle = ::CreateFileW(
            name, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, flags, 0);
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateFile, error);
        }
        return (handle);
    }

}

namespace w32 { namespace io {

    NamedPipe NamedPipe::create ( const string& name, dword size, bool async )
    {
        return (NamedPipe(claim(::create(name.data(), size, async))));
    }

    void NamedPipe::wait ( const string& name )
    {
        const ::BOOL result = ::WaitNamedPipeW(
            name.data(), NMPWAIT_WAIT_FOREVER);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(WaitNamedPipe, error);
        }
    }

    bool NamedPipe::wait ( const string& name, dword timeout )
    {
        const ::BOOL result = ::WaitNamedPipeW(name.data(), timeout);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error != ERROR_SEM_TIMEOUT )
            {
                UNCHECKED_WIN32C_ERROR(WaitNamedPipe, error);
            }
        }
        return (result != FALSE);
    }

    NamedPipe::NamedPipe ( const Handle& handle )
        : Channel(handle)
    {
    }

    NamedPipe::NamedPipe ( const string& name, bool async )
        : Channel(claim(::open(name.data(), async)))
    {
    }

    void NamedPipe::connect ()
    {
        const ::BOOL result = ::ConnectNamedPipe(handle(), 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ConnectNamedPipe, error);
        }
    }

    void NamedPipe::connect ( Transfer& transfer )
    {
        const ::BOOL result = ::ConnectNamedPipe(handle(), &transfer.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ConnectNamedPipe, error);
        }
    }

} }
