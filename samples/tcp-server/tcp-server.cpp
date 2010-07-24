// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/tcp/naive-server.hpp>
//#include <w32/net/tcp/threaded-server.hpp>

namespace {

    int transaction ( w32::net::sockstream& channel )
    {
        std::string message;
        std::getline(channel, message);
        channel << message << std::endl;
        return (0);
    }

}

#include <w32/net/tcp/naive-server.cpp>
//#include <w32/net/tcp/threaded-server.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.mt.lib" )
#pragma comment ( lib, "w32.net.lib" )
