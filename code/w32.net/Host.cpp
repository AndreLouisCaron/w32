// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
