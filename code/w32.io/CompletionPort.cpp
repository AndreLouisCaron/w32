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
 * @file w32.io/CompletionPort.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/CompletionPort.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( ::DWORD threads, ::HANDLE stream, ::ULONG_PTR key )
    {
        const ::HANDLE result =
            ::CreateIoCompletionPort(stream, 0, key, threads);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateIoCompletionPort, error);
        }
        return (result);
    }

    ::HANDLE allocate ( ::DWORD threads )
    {
        return (allocate(threads, INVALID_HANDLE_VALUE, 0));
    }

}

namespace w32 { namespace io {

    CompletionPort::CompletionPort ( dword threads )
        : Object(claim( ::allocate(threads) ))
    {
    }

    CompletionPort::CompletionPort
        ( const Stream& stream, Key key, dword threads )
        : Object(claim( ::allocate(threads, stream.handle(), key) ))
    {
    }

    void CompletionPort::bind ( const Stream& stream, Key key )
    {
        const ::HANDLE result = ::CreateIoCompletionPort
            (stream.handle(), handle(), key, 0);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateIoCompletionPort, error);
        }
    }

    void CompletionPort::bind ( const Stream& stream, void * key )
    {
        bind(stream, reinterpret_cast<Key>(key));
    }

    void CompletionPort::get ( Size& bytes, Key& key, Transfer *& transfer )
    {
        const ::BOOL result = ::GetQueuedCompletionStatus(
            handle(), &bytes, &key,
            &reinterpret_cast<::OVERLAPPED*&>(transfer), INFINITE
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ((error == ERROR_NETNAME_DELETED   )||
                (error == ERROR_CONNECTION_ABORTED)||
                (error == ERROR_HANDLE_EOF        ))
            {
                bytes = 0; key = 0; transfer = 0; return;
            }
            UNCHECKED_WIN32C_ERROR(GetQueuedCompletionStatus, error);
        }
    }

    bool CompletionPort::get
        ( Size& bytes, Key& key, Transfer *& transfer, Timespan timeout )
    {
        const ::BOOL result = ::GetQueuedCompletionStatus(
            handle(), &bytes, &key,
            &reinterpret_cast<::OVERLAPPED*&>(transfer), timeout.ticks()
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            //if ( error != !?WHAT_IS_THE_TIMEOUT_CODE?! ) {}
            if ((error == ERROR_NETNAME_DELETED   )||
                (error == ERROR_CONNECTION_ABORTED)||
                (error == ERROR_HANDLE_EOF        ))
            {
                bytes = 0; key = 0; transfer = 0; return (true);
            }
            UNCHECKED_WIN32C_ERROR(GetQueuedCompletionStatus, error);
        }
        return (result == TRUE);
    }

    void CompletionPort::put ( Size bytes, Key key, Transfer * transfer )
    {
        const ::BOOL result = ::PostQueuedCompletionStatus
            (handle(), bytes, key, reinterpret_cast<::OVERLAPPED*>(transfer));
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(PostQueuedCompletionStatus, error);
        }
    }

} }
