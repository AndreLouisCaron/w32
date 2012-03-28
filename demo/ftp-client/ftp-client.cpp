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

/*!
 * @file demo/ftp-client/ftp-client.cpp
 * @brief Simple FTP client.
 */

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
