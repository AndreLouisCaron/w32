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
 * @file w32.io/OutputFile.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/OutputFile.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE open ( ::LPCWSTR path, ::DWORD sharing, ::DWORD mode )
    {
        const ::HANDLE result = ::CreateFileW(
            path, GENERIC_WRITE, sharing, 0, mode, 0, 0
            );
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateFile,error);
        }
        return (result);
    }

}

namespace w32 { namespace io {

    const OutputFile::Mode OutputFile::Mode::open ()
    {
        return (OPEN_EXISTING);
    }

    const OutputFile::Mode OutputFile::Mode::create ()
    {
        return (CREATE_NEW);
    }

    const OutputFile::Mode OutputFile::Mode::replace ()
    {
        return (TRUNCATE_EXISTING);
    }

    const OutputFile::Mode OutputFile::Mode::squash ()
    {
        return (CREATE_ALWAYS);
    }

    const OutputFile::Mode OutputFile::Mode::append ()
    {
        return (OPEN_ALWAYS);
    }

    OutputFile::Mode::Mode ( Value value )
        : myValue(value)
    {
    }

    OutputFile::Mode::Value OutputFile::Mode::value () const
    {
        return (myValue);
    }

    OutputFile::OutputFile ( const string& path, const Mode& mode )
        : OutputStream(Object::claim(
              ::open(path.c_str(), 0, mode.value())
              ))
    {
    }

} }
