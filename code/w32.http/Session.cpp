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

#include <w32.http/Session.hpp>
#include <w32.http/Library.hpp>
#include <w32/Error.hpp>

namespace {

    ::HTTP_SERVER_SESSION_ID allocate ( const ::HTTPAPI_VERSION& version )
    {
        ::HTTP_SERVER_SESSION_ID handle = 0;
        const ::ULONG result = ::HttpCreateServerSession(version, &handle, 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpCreateServerSession, result);
        }
        return (handle);
    }

    void abandon ( ::HTTP_SERVER_SESSION_ID object ) {}
    void destroy ( ::HTTP_SERVER_SESSION_ID object )
    {
        const ::ULONG result = ::HttpCloseServerSession(object);
        if ( result != NO_ERROR ) {
            std::cerr << "[[[ " << w32::Error(result) << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace http {

    Session::Handle Session::claim ( ::HTTP_SERVER_SESSION_ID object )
    {
        return (Handle(object, &::destroy));
    }

    Session::Handle Session::proxy ( ::HTTP_SERVER_SESSION_ID object )
    {
        return (Handle(object, &::abandon));
    }

    Session::Session ( const Library::Version& version )
        : myHandle(claim( ::allocate(version.data()) ))
    {
    }

    const Session::Handle& Session::handle () const
    {
        return (myHandle);
    }

} }
