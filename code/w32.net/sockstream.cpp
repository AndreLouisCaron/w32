// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net/sockstream.hpp>

namespace w32 { namespace net {

    sockstream::sockstream ( StreamSocket& backend )
        : std::iostream(0), myBackend(backend), myBuffer(myBackend)
    {
        rdbuf(&myBuffer);
    }

    void sockstream::shutdown ( std::ios::openmode mode )
    {
        if ((mode&std::ios::in) && (mode&std::ios::out)) {
            myBackend.shutdown(w32::net::Socket::Shutdown::both());
        }
        else if ( mode & std::ios::in ) {
            myBackend.shutdown(w32::net::Socket::Shutdown::input());
        }
        else if ( mode & std::ios::out ) {
            myBackend.shutdown(w32::net::Socket::Shutdown::output());
        }
    }

} }
