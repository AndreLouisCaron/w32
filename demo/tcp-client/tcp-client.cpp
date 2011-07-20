// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/net/tcp/naive-client.hpp>
#include <w32.mt.hpp>
#include <w32.net.hpp>

namespace {

    int transaction
        ( int argc, wchar_t ** argv, w32::net::sockstream& channel )
    {
        w32::mt::sleep(w32::Timespan(100));
        
        const std::string request = "Hello, world!";
        channel << request << std::endl;
        std::string reply;
        if ( !std::getline(channel,reply) ) {
            std::cerr << "Could not get reply from server!" << std::endl;
        }
        if ( reply != request ) {
            std::cerr
                << "Reply '" << reply << "' doesn't match request '"
                << request << "'." << std::endl;
        }
        
        return (0);
    }

}

#include <w32/net/tcp/naive-client.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.mt.lib" )
#pragma comment ( lib, "w32.net.lib" )
