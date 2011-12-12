// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net/Context.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace net {

    Context::Context ()
    {
            // Clear the structure, just in case.
        ::ZeroMemory(&myData, sizeof(myData));
        
            // Initialize library.
        const int result = ::WSAStartup(MAKEWORD(2,2), &myData);
        if ( result != 0 ) {
            UNCHECKED_WIN32C_ERROR(WSAStartup,result);
        }
    }

    Context::~Context ()
    {
        const int result = ::WSACleanup();
        if ( result != 0 ) {
            UNCHECKED_WIN32C_ERROR(WSACleanup,result);
        }
    }

    Context::Data& Context::data ()
    {
        return (myData);
    }

    const Context::Data& Context::data () const
    {
        return (myData);
    }

    dword Context::version () const
    {
        return (MAKELONG(myData.wHighVersion, myData.wVersion));
    }

    astring Context::description () const
    {
        return (myData.szDescription);
    }

    astring Context::status () const
    {
        return (myData.szSystemStatus);
    }

} }
