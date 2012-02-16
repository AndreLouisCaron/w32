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

#include <w32.in/Session.hpp>
#include <w32.in/IStream.hpp>
#include <w32/Error.hpp>

namespace {

    ::HINTERNET establish ( ::LPCWSTR agent )
    {
        const ::DWORD access = INTERNET_OPEN_TYPE_DIRECT;
        const ::DWORD flags = 0; // INTERNET_FLAG_ASYNC, INTERNET_FLAG_OFFLINE;
        const ::HINTERNET result = ::InternetOpenW
            (agent, access, 0, 0, flags);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetOpen, error);
        }
        return (result);
    }

    void abandon ( ::HINTERNET object ) {}
    void destroy ( ::HINTERNET object )
    {
        const ::BOOL result = ::InternetCloseHandle(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace in {

    const Session::Handle Session::claim ( ::HINTERNET object )
    {
        return (Handle(object, &::destroy));
    }

    const Session::Handle Session::proxy ( ::HINTERNET object )
    {
        return (Handle(object, &::abandon));
    }

    Session::Session ( const string& agent )
        : myHandle(claim( ::establish(agent.c_str()) ))
    {
    }

    const Session::Handle& Session::handle () const
    {
        return (myHandle);
    }

    IStream Session::open ( const string& url )
    {
        return (IStream(*this, url));
    }

} }
