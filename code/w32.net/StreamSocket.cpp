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

#include <w32.net/StreamSocket.hpp>
#include <w32/Error.hpp>
#include <w32.io/Channel.hpp>
#include <w32.io/InputStream.hpp>
#include <w32.io/OutputStream.hpp>
#include <w32.io/Stream.hpp>
#include <w32.io/Transfer.hpp>

namespace w32 { namespace net {

    StreamSocket::StreamSocket ( const Handle& handle )
        : Socket(handle)
    {
    }

    StreamSocket::~StreamSocket ()
    {
    }

    int StreamSocket::put ( const void * buffer, int length )
    {
        const int result = ::send
            (handle(), static_cast<const char*>(buffer), length, 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(shutdown, error);
        }
        return (result);
    }

    int StreamSocket::get ( void * buffer, int length )
    {
        const int result = ::recv
            (handle(), static_cast<char*>(buffer), length, 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error == WSAECONNRESET ) {
                return (0);
            }
            if ( error == WSAEWOULDBLOCK ) {
                return (-1);
            }
            UNCHECKED_WIN32C_ERROR(recv, error);
        }
        return (result);
    }

    bool StreamSocket::put ( const void * data, dword size,
                             io::Transfer& transfer )
    {
        return (put(data, size, transfer.data()));
    }

    bool StreamSocket::put ( const void * data, dword size,
                             ::OVERLAPPED& transfer )
    {
        const ::SOCKET socket = this->handle();
        const ::HANDLE handle = reinterpret_cast<::HANDLE>(socket);

        const ::BOOL result = ::WriteFile
            (handle, data, size, 0, &transfer);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if (error == ERROR_IO_PENDING) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(WriteFile, error);
        }
        return (true);
    }

    bool StreamSocket::get ( void * data, dword size,
                             ::OVERLAPPED& transfer )
    {
        const ::SOCKET socket = this->handle();
        const ::HANDLE handle = reinterpret_cast<::HANDLE>(socket);

        const ::BOOL result = ::ReadFile
            (handle, data, size, 0, &transfer);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if (error == ERROR_IO_PENDING) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(ReadFile, error);
        }
        return (true);
    }

    bool StreamSocket::get ( void * data, dword size,
                             io::Transfer& transfer )
    {
        return (get(data, size, transfer.data()));
    }

    int StreamSocket::put ( Buffer& buffer )
    {
        ::DWORD bytes = 0; ::DWORD flags = 0;
        const int result = ::WSASend
            (handle(), &buffer.data(), 1, &bytes, flags, 0, 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            UNCHECKED_WIN32C_ERROR(WSASend, error);
        }
        return (result);
    }

    int StreamSocket::get ( Buffer& buffer )
    {
        ::DWORD bytes = 0; ::DWORD flags = 0;
        const int result = ::WSARecv
            (handle(), &buffer.data(), 1, &bytes, &flags, 0, 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error == WSAECONNRESET ) {
                return (0);
            }
            UNCHECKED_WIN32C_ERROR(WSARecv, error);
        }
        return (result);
    }

    void StreamSocket::put ( Buffer& buffer, io::Transfer& transfer )
    {
        ::DWORD bytes = 0; ::DWORD flags = 0;
        const int result = ::WSASend
            (handle(), &buffer.data(), 1, &bytes, flags, &transfer.data(), 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error != WSA_IO_PENDING ) {
                UNCHECKED_WIN32C_ERROR(WSASend, error);
            }
        }
    }

    void StreamSocket::get ( Buffer& buffer, io::Transfer& transfer )
    {
        ::DWORD bytes = 0; ::DWORD flags = 0;
        const int result = ::WSARecv
            (handle(), &buffer.data(), 1, &bytes, &flags, &transfer.data(), 0);
        if ( result == SOCKET_ERROR )
        {
            const int error = ::WSAGetLastError();
            if ( error != WSA_IO_PENDING ) {
                UNCHECKED_WIN32C_ERROR(WSARecv, error);
            }
        }
    }

    void StreamSocket::cancel ()
    {
        const ::SOCKET socket = this->handle();
        const ::HANDLE handle = reinterpret_cast<::HANDLE>(socket);

        #if _WIN32_WINNT < _WIN32_WINNT_VISTA
        const ::BOOL result = ::CancelIo(handle);
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CancelIo, error);
        }
        #else
        const ::BOOL result = ::CancelIoEx(handle, 0);
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CancelIoEx, error);
        }
        #endif
    }

    bool StreamSocket::cancel ( io::Transfer& transfer )
    {
        const ::SOCKET socket = this->handle();
        const ::HANDLE handle = reinterpret_cast<::HANDLE>(socket);

        const ::BOOL result = ::CancelIoEx(handle, &transfer.data());
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            if (error == ERROR_NOT_FOUND) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(CancelIoEx, error);
        }
        return (true);
    }

    dword StreamSocket::finish ( io::Transfer& transfer )
    {
        const ::SOCKET socket = this->handle();
        const ::HANDLE handle = reinterpret_cast<::HANDLE>(socket);

        dword xferred = 0;
        const ::BOOL result = ::GetOverlappedResult
            (handle, &transfer.data(), &xferred, TRUE);
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            if (result == ERROR_NOT_FOUND) {
                return (0);
            }
            if (result == ERROR_HANDLE_EOF) {
                return (0);
            }
            UNCHECKED_WIN32C_ERROR(GetOverlappedResult, error);
        }
        return (xferred);
    }

    StreamSocket::operator io::Channel () const
    {
            // Yes, ::SOCKET can be cast into ::HANDLE to use in calls to
            // ReadFile() and WriteFile()...
        const ::SOCKET socket = handle();
        return (io::Channel(Object::proxy(
            reinterpret_cast< ::HANDLE >(socket)
            )));
    }

    StreamSocket::operator io::InputStream () const
    {
            // Yes, ::SOCKET can be cast into ::HANDLE to use in calls to
            // ReadFile() and WriteFile()...
        const ::SOCKET socket = handle();
        return (io::InputStream(Object::proxy(
            reinterpret_cast< ::HANDLE >(socket)
            )));
    }

    StreamSocket::operator io::OutputStream () const
    {
            // Yes, ::SOCKET can be cast into ::HANDLE to use in calls to
            // ReadFile() and WriteFile()...
        const ::SOCKET socket = handle();
        return (io::OutputStream(Object::proxy(
            reinterpret_cast< ::HANDLE >(socket)
            )));
    }

    StreamSocket::operator io::Stream () const
    {
            // Yes, ::SOCKET can be cast into ::HANDLE to use in calls to
            // ReadFile() and WriteFile()...
        const ::SOCKET socket = handle();
        return (io::Stream(Object::proxy(
            reinterpret_cast< ::HANDLE >(socket)
            )));
    }

} }
