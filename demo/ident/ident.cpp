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

#include <WinSock2.h>
#include <Ws2TcpIp.h>
#include <IpHlpApi.h>
#include <Windows.h>

#include <w32.hpp>
#include <w32.cr.hpp>
#include <w32.ipc.hpp>
#include <w32.sy.hpp>

#include <iostream>
#include <string>
#include <sstream>

namespace {

    ::PMIB_TCPTABLE2 read_tcp_table ()
    {
        ::DWORD size = 0;
        ::PMIB_TCPTABLE2 data = 0;
        ::ULONG error = ::GetTcpTable2(0, &size, FALSE);
        while (error == ERROR_INSUFFICIENT_BUFFER)
        {
            operator delete(data);
            data = static_cast<::PMIB_TCPTABLE2>(operator new(size));
            error = ::GetTcpTable2(data, &size, FALSE);
        }
        if (error != NO_ERROR)
        {
            operator delete(data); data = 0;
            if (error == ERROR_INVALID_PARAMETER)
            {
                // ...
            }
            if (error == ERROR_NOT_SUPPORTED)
            {
                // ...
            }
            std::cerr << "Error: " << error << std::endl;
        }
        return (data);
    }

    w32::string mangle ( const w32::string& username )
    {
        // Get a cryptographic context for user name mangling.
        w32::cr::Provider::Hints hints;
        hints
            .silent()
            .verifyContext();
        w32::cr::Provider provider
            (w32::cr::Provider::Type::rsafull(), hints);

        // Mangle the user name, for security.
        const w32::astring name(username, w32::Codepage::utf8());
        const w32::cr::Hash hash =
            w32::cr::sha1(provider, name.data(), name.size());
        return (w32::cr::convert(hash.data()));
    }

    std::ostream& usage (std::ostream& stream)
    {
        return (stream
            << std::endl
            <<   "  Usage: ident server-port client-port                    \n"
            <<   "         ident --help                                     \n"
            <<   "                                                          \n"
            <<   "  Arguments:                                              \n"
            <<   "    server-port: integer in [0,65536).                    \n"
            <<   "    client-port: integer in [0,65536).                    \n"
            <<   "                                                          \n"
            <<   "  Outputs an ident[1] service response to a query for the \n"
            <<   "  server (this comptuer) port and client (the remote      \n"
            <<   "  computer) port provided as arguments to the command.    \n"
            <<   "                                                          \n"
            <<   "  In this command, the computer running the process is    \n"
            <<   "  the server.  This is meant as a diagnostic tool for     \n"
            <<   "  implementing the ident service, not as a ident client.  \n"
            <<   "                                                          \n"
            <<   "  [1]: http://tools.ietf.org/html/rfc1413                 \n"
            << std::endl);
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        // Respond to usage request.
        if ((argc >= 2) && (::wcscmp(argv[1],L"--help")==0)) {
            std::cout
                << usage
                << std::endl;
            return (EXIT_SUCCESS);
        }

        // Parse command-line arguments.
        ::DWORD client_port = 0;
        ::DWORD server_port = 0;
        int errors = 0;
        if (argc >= 2)
        {
            std::wistringstream stream(argv[1]);
            if (!(stream >> server_port) ||
                (server_port == 0) || (server_port > 65535))
            {
                std::cerr
                    << "Invalid server port: '" << argv[1] << "'."
                    << std::endl;
                ++errors;
            }
        }
        else {
            std::cerr
                << "No server port."
                << std::endl;
            ++errors;
        }
        if (argc >= 3)
        {
            std::wistringstream stream(argv[2]);
            if (!(stream >> client_port) ||
                (client_port == 0) || (client_port > 65535))
            {
                std::cerr
                    << "Invalid client port: '" << argv[2] << "'."
                    << std::endl;
                ++errors;
            }
        }
        else {
            std::cerr
                << "No client port."
                << std::endl;
            ++errors;
        }

        // Don't execute if validating any argument failed.
        if (errors > 0) {
            return (EXIT_FAILURE);
        }

        // Fetch current table state.
        ::PMIB_TCPTABLE2 table = ::read_tcp_table();

        // Locate a process with a connection that matches the query.
        std::string username;
        for (::DWORD i=0; (i < table->dwNumEntries); ++i)
        {
            // Port numbers in TCP table are in network byte order.
            const ::MIB_TCPROW2& row = table->table[i];
            if ((row.dwState == MIB_TCP_STATE_ESTAB) &&
                (row.dwLocalPort  == ::ntohs(server_port)) &&
                (row.dwRemotePort == ::ntohs(client_port)))
            {
                // Find the user account owning the process.
                w32::ipc::Process::Access access;
                access
                    .query_information()
                    ;
                w32::ipc::Process process(row.dwOwningPid, access);
                w32::sy::Token token = w32::sy::Token::of(process);
                w32::sy::User user(token);
                w32::sy::Account account(user);
                const w32::string name = account.username();

                // Mangle the name and encode it to ASCII.
                username = w32::astring(mangle(name));
            }
        }

        // Get rid of the current state.
        operator delete(table);

        // Reply.
        if (username.empty())
        {
            std::cout
                << server_port << ", " << client_port
                << " : ERROR : UNKNOWN-ERROR"
                << std::endl;
        }
        else
        {
            std::cout
                << server_port << ", " << client_port
                << " : USERID : OTHER : " << username
                << std::endl;
        }

        return (EXIT_SUCCESS);
    }

}

#pragma comment ( lib, "IpHlpApi.lib" )
#pragma comment ( lib, "ws2_32.lib" )

#include <w32/app/console-program.cpp>
