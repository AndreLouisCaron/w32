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

#include <w32.net/Host.hpp>
#include <w32.net/HostName.hpp>
#include <w32/Error.hpp>

namespace {

    const ::hostent * fetch ( const char * name )
    {
            // Note: static entry allocated in thread-local storage.
        struct ::hostent * entry = ::gethostbyname(name);
        if ( entry == 0 ) {
            UNCHECKED_WIN32C_ERROR(gethostbyname,::WSAGetLastError());
        }
        return (entry);
    }

    const ::hostent * fetch ()
    {
        const w32::astring name = w32::net::hostname();
        return (fetch(name.c_str()));
    }

}

namespace w32 { namespace net {

    const ::hostent * Host::fetch ( const void * data, int size, int type )
    {
            // Note: static entry allocated in thread-local storage.
        struct ::hostent * entry = ::gethostbyaddr
            (reinterpret_cast<const char*>(data), size, type);
        if ( entry == 0 ) {
            UNCHECKED_WIN32C_ERROR(gethostbyaddr,::WSAGetLastError());
        }
        return (entry);
    }

    Host::Host ()
    {
        ::memcpy(&myData, ::fetch(), sizeof(myData));
    }

    Host::Host ( const astring& name )
    {
        ::memcpy(&myData, ::fetch(name.c_str()), sizeof(myData));
    }

    Host::Host ( const string& name )
    {
        const astring aname(name, Codepage::ansi());
        ::memcpy(&myData, ::fetch(aname.c_str()), sizeof(myData));
    }

    const Host::Data& Host::data () const
    {
        return (myData);
    }

    const Family Host::family () const
    {
        return (Family::of(*this));
    }

    astring Host::name () const
    {
        return (astring(myData.h_name));
    }

    size_t Host::addresses () const
    {
        size_t count = 0;
        while ( myData.h_addr_list[count] != 0 ) {
            ++count;
        }
        return (count);
    }

#if 0
        // For IPv4 only!
    server.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr_list[0][0];
    server.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr_list[0][1];
    server.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr_list[0][2];
    server.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr_list[0][3];
#endif

    Host::Aliases::Aliases ( const Host& host )
        : mstring(string(L"foo\0bar\0",8))
    {
    }

} }
