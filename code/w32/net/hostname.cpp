// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/hostname.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace w32 { namespace net {

    astring hostname ()
    {
            // This is documented to be at most 256 characters.
        char buffer[257];
        buffer[256] = '\0';
        const int result = ::gethostname(buffer, 256);
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(gethostname, ::WSAGetLastError());
        }
        return (astring(buffer));
    }

} }
