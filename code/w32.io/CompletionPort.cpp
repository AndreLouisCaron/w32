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
#include <w32.io/Notification.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( ::DWORD threads, ::HANDLE stream, ::ULONG_PTR data )
    {
        const ::HANDLE result =
            ::CreateIoCompletionPort(stream, 0, data, threads);
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
        ( const Stream& stream, Data data, dword threads )
        : Object(claim( ::allocate(threads, stream.handle(), data) ))
    {
    }

    void CompletionPort::bind ( ::HANDLE object, Data data )
    {
        const ::HANDLE result = ::CreateIoCompletionPort
            (object, handle(), data, 0);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateIoCompletionPort, error);
        }
    }

    void CompletionPort::bind ( ::HANDLE object, void * data )
    {
        bind(object, reinterpret_cast<Data>(data));
    }

    void CompletionPort::bind ( ::SOCKET object, Data data )
    {
        bind(reinterpret_cast<::HANDLE>(object), data);
    }

    void CompletionPort::bind ( ::SOCKET object, void * data )
    {
        bind(reinterpret_cast<::HANDLE>(object), data);
    }

    void CompletionPort::bind ( const Stream& stream, Data data )
    {
        bind(stream.handle(), data);
    }

    void CompletionPort::bind ( const Stream& stream, void * data )
    {
        bind(stream.handle(), reinterpret_cast<Data>(data));
    }

    void CompletionPort::next ( Size& bytes, Data& data, Transfer *& transfer )
    {
        const ::BOOL result = ::GetQueuedCompletionStatus(
            handle(), &bytes, &data,
            &reinterpret_cast<::OVERLAPPED*&>(transfer), INFINITE
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ((error == ERROR_NETNAME_DELETED   )||
                (error == ERROR_CONNECTION_ABORTED)||
                (error == ERROR_HANDLE_EOF        )||
                (error == ERROR_OPERATION_ABORTED ))
            {
                bytes = 0; data = 0; transfer = 0; return;
            }
            UNCHECKED_WIN32C_ERROR(GetQueuedCompletionStatus, error);
        }
    }

    bool CompletionPort::next
        ( Size& bytes, Data& data, Transfer *& transfer, Timespan timeout )
    {
        const ::BOOL result = ::GetQueuedCompletionStatus(
            handle(), &bytes, &data,
            &reinterpret_cast<::OVERLAPPED*&>(transfer), timeout.ticks()
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ((error == ERROR_NETNAME_DELETED   )||
                (error == ERROR_CONNECTION_ABORTED)||
                (error == ERROR_HANDLE_EOF        )||
                (error == ERROR_OPERATION_ABORTED )||
                (error == WAIT_TIMEOUT            ))
            {
                bytes = 0; data = 0; transfer = 0; return (true);
            }
            UNCHECKED_WIN32C_ERROR(GetQueuedCompletionStatus, error);
        }
        return (result == TRUE);
    }

    void CompletionPort::post ( Size size, Data data, ::OVERLAPPED * transfer )
    {
        const ::BOOL result = ::PostQueuedCompletionStatus
            (handle(), size, data, transfer);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(PostQueuedCompletionStatus, error);
        }
    }

    void CompletionPort::post ( Size size, void * data,
                                ::OVERLAPPED * transfer )
    {
        return (post(size, reinterpret_cast<Data>(data), transfer));
    }

    void CompletionPort::post ( Size size, Data data, Transfer * transfer )
    {
        return (post(size, data, reinterpret_cast<::OVERLAPPED*>(transfer)));
    }

    void CompletionPort::unblock_consumers ()
    {
        post(Size(0), Data(0), static_cast<::OVERLAPPED*>(0));
    }

    Notification CompletionPort::next ()
    {
        Size size = 0;
        Data data = 0;
        ::OVERLAPPED * transfer = 0;
        const ::BOOL result = ::GetQueuedCompletionStatus
            (handle(), &size, &data, &transfer, INFINITE);
        ::DWORD status = NO_ERROR;
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ((error == ERROR_NETNAME_DELETED   )||
                (error == ERROR_CONNECTION_ABORTED)||
                (error == ERROR_HANDLE_EOF        )||
                (error == ERROR_OPERATION_ABORTED ))
            {
                status = error;
            }
            else {
                UNCHECKED_WIN32C_ERROR(GetQueuedCompletionStatus, error);
            }
        }
        return (Notification(status, data,
                             reinterpret_cast<Transfer*>(transfer), size));
    }

    Notification CompletionPort::next ( Timespan timeout )
    {
        Size size = 0;
        Data data = 0;
        ::OVERLAPPED * transfer = 0;
        const ::BOOL result = ::GetQueuedCompletionStatus
            (handle(), &size, &data, &transfer, timeout.ticks());
        ::DWORD status = NO_ERROR;
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ((error == ERROR_NETNAME_DELETED   )||
                (error == ERROR_CONNECTION_ABORTED)||
                (error == ERROR_HANDLE_EOF        )||
                (error == WAIT_TIMEOUT            )||
                (error == ERROR_OPERATION_ABORTED ))
            {
                status = error;
            }
            else {
                UNCHECKED_WIN32C_ERROR(GetQueuedCompletionStatus, error);
            }
        }
        return (Notification(status, data,
                             reinterpret_cast<Transfer*>(transfer), size));
    }

    Notification CompletionPort::peek ()
    {
        return (next(Timespan()));
    }

} }
