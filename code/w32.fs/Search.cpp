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

#include <w32.fs/Search.hpp>
#include <w32/Error.hpp>
#include <iostream>
#include <sstream>

namespace {

    ::HANDLE find ( ::LPCWSTR pattern, ::WIN32_FIND_DATAW& result )
    {
        const ::HANDLE handle = ::FindFirstFileW(pattern, &result);
        if ( handle == INVALID_HANDLE_VALUE ) {
            UNCHECKED_WIN32C_ERROR(FindFirstFile, ::GetLastError());
        }
        return (handle);
    }

    void release ( ::HANDLE object )
    {
        const ::BOOL result = ::FindClose(object);
        if ( result == FALSE ) {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace fs {

    const Search::Handle Search::claim ( ::HANDLE object )
    {
        return (Handle(object, &::release));
    }

    Search::Search ( const string& pattern, Result& result )
        : Object(claim(::find(pattern.data(), result.data())))
    {
    }

    bool Search::next ( Result& result )
    {
        const ::BOOL status = ::FindNextFileW(handle(),&result.data());
        if ( status == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_FILES ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(FindNextFile,error);
        }
        return (true);
    }

    Search::Result::Result ()
    {
        ::ZeroMemory(&myData,sizeof(myData));
    }

    Search::Result::Data& Search::Result::data ()
    {
        return (myData);
    }

    const Search::Result::Data& Search::Result::data () const
    {
        return (myData);
    }

    string Search::Result::name () const
    {
        return (myData.cFileName);
    }

    Attributes Search::Result::attributes () const
    {
        return (Attributes(myData.dwFileAttributes));
    }

    Time Search::Result::creation () const
    {
        return (Time(myData.ftCreationTime));
    }

    Time Search::Result::access () const
    {
        return (Time(myData.ftLastAccessTime));
    }

    Time Search::Result::modification () const
    {
        return (Time(myData.ftLastWriteTime));
    }

    qword Search::Result::size () const
    {
        return ((qword(myData.nFileSizeHigh)<<32)|qword(myData.nFileSizeLow));
    }

} }
