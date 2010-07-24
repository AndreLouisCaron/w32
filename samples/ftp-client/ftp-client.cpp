// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net.hpp>
#include <w32.hpp>
#include <w32.mt.hpp>
#include <fstream>
#include <sstream>
#include "ftp.hpp"

namespace ftp {

    using namespace w32;
    using namespace w32::net;

    void ls ( std::iostream& io, std::ostream& out )
    {
            // Ask the server where it'd like us to query.
        ftp::pasv _; io >> _; std::cout << _;
        
        int address[4] = { 0 }; int port[2] = { 0 };
        { std::istringstream input(_.message());
            std::getline(input, std::string(), '(');
            (input >> address[0]).ignore(1);
            (input >> address[1]).ignore(1);
            (input >> address[2]).ignore(1);
            (input >> address[3]).ignore(1);
            (input >>    port[0]).ignore(1);
            (input >>    port[1]).ignore(1);
        }
        const ipv4::EndPoint endpoint(
            address[0], address[1], address[2], address[3],
            256 * port[0] + port[1]);
        
            // Establish a streamed data connection.
        tcp::Stream data(endpoint);
        sockstream stream(data);
        
            // Request the transfer!
        { ftp::list _; _(io,stream,out); std::cout << _; }
    }

    void dir ( std::iostream& io, std::ostream& out )
    {
            // Ask the server where it'd like us to query.
        ftp::pasv _; io >> _; std::cout << _;
        
        int address[4] = { 0 }; int port[2] = { 0 };
        { std::istringstream input(_.message());
            std::getline(input, std::string(), '(');
            (input >> address[0]).ignore(1);
            (input >> address[1]).ignore(1);
            (input >> address[2]).ignore(1);
            (input >> address[3]).ignore(1);
            (input >>    port[0]).ignore(1);
            (input >>    port[1]).ignore(1);
        }
        const ipv4::EndPoint endpoint(
            address[0], address[1], address[2], address[3],
            256 * port[0] + port[1]);
        
            // Establish a streamed data connection.
        tcp::Stream data(endpoint);
        sockstream stream(data);
        
            // Request the transfer!
        { ftp::nlst _; _(io,stream,out); std::cout << _; }
    }

    void get
        ( std::iostream& io, const std::string& path, std::ostream& out )
    {
            // Ask the server where it'd like us to query.
        ftp::pasv _; io >> _; std::cout << _;
        
        int address[4] = { 0 }; int port[2] = { 0 };
        { std::istringstream input(_.message());
            std::getline(input, std::string(), '(');
            (input >> address[0]).ignore(1);
            (input >> address[1]).ignore(1);
            (input >> address[2]).ignore(1);
            (input >> address[3]).ignore(1);
            (input >>    port[0]).ignore(1);
            (input >>    port[1]).ignore(1);
        }
        const ipv4::EndPoint endpoint(
            address[0], address[1], address[2], address[3],
            256 * port[0] + port[1]);
        
            // Establish a streamed data connection.
        tcp::Stream data(endpoint);
        sockstream stream(data);
        
            // Request the transfer!
        { ftp::retr _(path); _(io,stream,out); std::cout << _; }
    }

    void test ( sockstream& io )
    {
            // Wait for server info.
        { ftp::welcome _; io >> _; std::cout << _; }
        
            // Attempt login.
        { ftp::login _("anonymous", "anonymous");
            io >> _; std::cout << _;
        }
        
            // Request remote system information.
        { ftp::syst _; io >> _; std::cout << _; }
        
            // Switch to binary (image) mode.
        { ftp::type _('I'); io >> _; std::cout << _; }
        
            // Get connection status.
        { ftp::stat _; io >> _; std::cout << _; }
        
            // Switch to passive mode, we might be behind a
            // firewall, and it makes the code simpler.
        { ftp::pasv _; io >> _; std::cout << _; }
        
            // Ask in which remote folder we're located.
        { ftp::pwd _; io >> _; std::cout << _; }
        
            // Try switching to commonly named sub-folder.
        { ftp::cwd _("/pub"); io >> _; std::cout << _; }
        
            // Check results of switching...
        { ftp::pwd _; io >> _; std::cout << _; }
        
            // Get sub-folder listing...
        ls(io, std::cout);
        
            // Transfer a file.
        const std::string path = "robots.txt";
        { std::ofstream file(path.c_str(), std::ios::binary);
            get(io, path, file);
        }
        
            // End connection politely!
        { ftp::quit _; io >> _; std::cout << _; }
    }

    void ls ( sockstream& io, ipv4::EndPoint local )
    {
        tcp::Listener listener(local, 1);
        
        // -> "port 192,168,1,102,19,137"
        // <- "200 ..."
        // -> "list"
        // <- "150 ..."
    }

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
    const w32::net::Context _;
        
            // ftp.ens.fr
        const w32::net::ipv4::Address server(168,143,19,69);
        
        w32::net::tcp::Stream control
            (w32::net::ipv4::EndPoint(server,21));
        w32::net::sockstream channel(control);
        ftp::test(channel);
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.mt.lib" )
#pragma comment ( lib, "w32.net.lib" )
