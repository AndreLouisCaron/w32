// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.fs.hpp>
#include <w32.in.hpp>
#include <fstream>
#include <sstream>
#include "ftp.hpp"

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // Initialize.
        w32::in::Session session("Internet Explorer");
        
            // Connect to the server.
        const w32::string url
            ("ftp://pumpking:Bonjour!@mybooklive/");
        w32::in::ftp::Connection connection(session, url);
        
            // Perform lising of root folder.
        connection.path("pumpking");
        w32::in::ftp::Listing::Result result;
        w32::in::ftp::Listing listing(connection, result);
        do {
            std::wcout << result.name();
            if ( result.attributes().folder() ) {
                std::wcout << "/";
            }
            std::wcout << std::endl;
        }
        while ( listing.next(result) );
        
            // All is well and good!
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.fs.lib" )
#pragma comment ( lib, "w32.in.lib" )
