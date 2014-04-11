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
 * @file w32.io/OutputStream.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/OutputStream.hpp>
#include <w32.io/Transfer.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace io {

    OutputStream::OutputStream ( const Handle& handle )
        : Stream(handle)
    {
    }

    dword OutputStream::put ( const void * data, dword size )
    {
        ::DWORD xferred = 0;
        const ::BOOL result = ::WriteFile(
            handle(), data, size, &xferred, 0
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if (error == ERROR_NO_DATA) {
                return (0);
            }
            UNCHECKED_WIN32C_ERROR(WriteFile, error);
        }
        return (xferred);
    }

    bool OutputStream::put ( const void * data, dword size, Transfer& xfer, dword& xferred )
    {
        return (put(data, size, xfer.data(), xferred));
    }

    bool OutputStream::put ( const void * data, dword size,
                             ::OVERLAPPED& xfer, dword& xferred )
    {
        const ::BOOL result = ::WriteFile(
            handle(), data, size, &xferred, &xfer
            );
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

} }
