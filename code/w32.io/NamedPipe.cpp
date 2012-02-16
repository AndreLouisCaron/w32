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
