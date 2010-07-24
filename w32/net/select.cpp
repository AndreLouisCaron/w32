// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/select.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace net {

    void select ( Set& read, Set& write, Set& errors )
    {
        const int result = ::select(
            0, &read.data(), &write.data(), &errors.data(), 0
            );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(select, ::WSAGetLastError());
        }
    }

    bool select ( Set& read, Set& write, Set& errors, const Timespan& timeout )
    {
        const int result = ::select(
            0, &read.data(), &write.data(), &errors.data(), 0
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(select, ::WSAGetLastError());
        }
        
            // Check if call timed-out!
        return (result > 0);
    }

} }
