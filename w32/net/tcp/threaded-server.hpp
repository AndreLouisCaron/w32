#ifndef _win32c_net_tcp_threaded_server_hpp__
#define _win32c_net_tcp_threaded_server_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net.hpp>

namespace {

    int transaction
        ( int argc, wchar_t ** argv, w32::net::sockstream& channel );

}

#endif /* _win32c_net_tcp_threaded_server_hpp__ */
