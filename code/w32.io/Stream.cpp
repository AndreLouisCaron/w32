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
 * @file w32.io/Stream.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/Stream.hpp>
#include <w32.io/Transfer.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace io {

    const Stream::Type Stream::Type::character ()
    {
        return (FILE_TYPE_CHAR);
    }

    const Stream::Type Stream::Type::disk ()
    {
        return (FILE_TYPE_DISK);
    }

    const Stream::Type Stream::Type::remote ()
    {
        return (FILE_TYPE_REMOTE);
    }

    const Stream::Type Stream::Type::ipc ()
    {
        return (FILE_TYPE_PIPE);
    }

    const Stream::Type Stream::Type::unknown ()
    {
        return (FILE_TYPE_UNKNOWN);
    }

    Stream::Type Stream::Type::of ( const Stream& stream )
    {
        const ::DWORD result = ::GetFileType(stream.handle());
        if ( result == FILE_TYPE_UNKNOWN ) {
            const ::DWORD error = ::GetLastError();
            if ( error != ERROR_SUCCESS ) {
                UNCHECKED_WIN32C_ERROR(GetFileType,error);
            }
        }
        return (Stream::Type(result));
    }

    Stream::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Stream::Stream ( const Handle& handle )
        : Object(handle)
    {
    }

    Stream::Size Stream::size () const
    {
        ::LARGE_INTEGER value = { 0 };
        const ::BOOL result = ::GetFileSizeEx(handle(),&value);
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetFileSizeEx,::GetLastError());
        }
        return (Stream::Size(value));
    }

    Stream::Position Stream::position () const
    {
        ::LARGE_INTEGER distance = { 0 };
        ::LARGE_INTEGER value = { 0 };
        const ::BOOL result = ::SetFilePointerEx(
            handle(), distance, &value, FILE_CURRENT
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetFilePointerEx,::GetLastError());
        }
        return (Stream::Position(value));
    }

    void Stream::position ( const Position& value ) const
    {
        const ::BOOL result = ::SetFilePointerEx(
            handle(), value.value(), 0, FILE_CURRENT
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetFilePointerEx,::GetLastError());
        }
    }

    void Stream::cancel ()
    {
#if _WIN32_WINNT < _WIN32_WINNT_VISTA
        const ::BOOL result = ::CancelIo(handle());
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CancelIo, error);
        }
#else
        const ::BOOL result = ::CancelIoEx(handle(), 0);
        if (result == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CancelIoEx, error);
        }
#endif
    }

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
    bool Stream::cancel ( Transfer& transfer )
    {
        const ::BOOL result = ::CancelIoEx(handle(), &transfer.data());
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
#endif

    dword Stream::finish ( Transfer& transfer )
    {
        dword xferred = 0;
        const ::BOOL result = ::GetOverlappedResult
            (handle(), &transfer.data(), &xferred, TRUE);
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

    Stream::Builder::Builder ()
        : myDesiredAccess(0)
        , myShareMode(0)
        , mySecurityAttributes(0)
        , myCreationDisposition(0)
        , myFlagsAndAttributes(0)
        , myTemplateFile(0)
    {
    }

    Stream::Builder& Stream::Builder::generic_read ()
    {
        myDesiredAccess |= GENERIC_READ;
        return (*this);
    }

    Stream::Builder& Stream::Builder::generic_write ()
    {
        myDesiredAccess |= GENERIC_WRITE;
        return (*this);
    }

    Stream::Builder& Stream::Builder::share_read ()
    {
        myShareMode |= FILE_SHARE_READ;
        return (*this);
    }

    Stream::Builder& Stream::Builder::share_write ()
    {
        myShareMode |= FILE_SHARE_WRITE;
        return (*this);
    }

    Stream::Builder& Stream::Builder::share_delete ()
    {
        myShareMode |= FILE_SHARE_DELETE;
        return (*this);
    }

    Stream::Builder& Stream::Builder::create_always ()
    {
        myCreationDisposition |= CREATE_ALWAYS;
        return (*this);
    }

    Stream::Builder& Stream::Builder::create_new ()
    {
        myCreationDisposition |= CREATE_NEW;
        return (*this);
    }

    Stream::Builder& Stream::Builder::open_always ()
    {
        myCreationDisposition |= OPEN_ALWAYS;
        return (*this);
    }

    Stream::Builder& Stream::Builder::open_existing ()
    {
        myCreationDisposition |= OPEN_EXISTING;
        return (*this);
    }

    Stream::Builder& Stream::Builder::truncate_existing ()
    {
        myCreationDisposition |= TRUNCATE_EXISTING;
        return (*this);
    }

    Stream::Builder& Stream::Builder::no_buffering ()
    {
        myFlagsAndAttributes |= FILE_FLAG_NO_BUFFERING;
        return (*this);
    }

    Stream::Builder& Stream::Builder::overlapped ()
    {
        myFlagsAndAttributes |= FILE_FLAG_OVERLAPPED;
        return (*this);
    }

    Stream::Builder& Stream::Builder::sequential_scan ()
    {
        myFlagsAndAttributes |= FILE_FLAG_SEQUENTIAL_SCAN;
        return (*this);
    }

    Stream::Builder& Stream::Builder::write_through ()
    {
        myFlagsAndAttributes |= FILE_FLAG_WRITE_THROUGH;
        return (*this);
    }

    Stream::Handle Stream::Builder::open (const string& path) const
    {
        const ::HANDLE handle = ::CreateFileW(
            path.data(), myDesiredAccess, myShareMode, mySecurityAttributes,
            myCreationDisposition, myFlagsAndAttributes, myTemplateFile);
        if (handle == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Failure!!!" << std::endl;
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateFile, error);
        }
        std::cerr << "Stream::Builder::open(): " << handle << std::endl;
        return (Stream::claim(handle));
    }

} }
