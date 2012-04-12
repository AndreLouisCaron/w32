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

#include "ftp.hpp"
#include <w32.cr.hpp>
#include <w32.fs.hpp>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "Strategy.hpp"

namespace {

    const w32::Codepage utf8 = w32::Codepage::utf8();

    w32::string resolve_folder
        ( const std::vector<w32::string>& path )
    {
        std::wostringstream out;
        for ( std::size_t i = 0; (i < path.size()); ++i ) {
            out << path[i] << L'\\';
        }
        return (out.str());
    }

    w32::string resolve_file
        ( const std::vector<w32::string>& path )
    {
        std::wostringstream out;
        for ( std::size_t i = 0; (i < path.size()-1); ++i ) {
            out << path[i] << L'\\';
        }
        out << path[path.size()-1];
        return (out.str());
    }

    w32::string resolve_folder
        ( const std::vector<w32::string>& path, const w32::string& name )
    {
        std::wostringstream out;
        for ( std::size_t i = 0; (i < path.size()); ++i ) {
            out << path[i] << L'\\';
        }
        out << name << L'\\';
        return (out.str());
    }

    w32::string resolve_file
        ( const std::vector<w32::string>& path, const w32::string& name )
    {
        std::wostringstream out;
        for ( std::size_t i = 0; (i < path.size()); ++i ) {
            out << path[i] << L'\\';
        }
        out << name;
        return (out.str());
    }

    w32::string search_pattern
        ( const std::vector<w32::string>& path )
    {
        return (resolve_file(path,L"*"));
    }

    inline w32::astring encode ( const w32::string& x )
    {
        return (w32::astring(x, utf8));
    }

    inline w32::astring encode ( const std::wstring& x )
    {
        return (w32::astring(x.c_str(), utf8));
    }

    inline w32::string decode ( const w32::astring& x )
    {
        return (w32::string(x, utf8));
    }

    inline w32::string decode ( const char * x )
    {
        return (w32::string(x, utf8));
    }

    w32::astring virtual_path
        ( const std::vector<w32::string>& path )
    {
        std::wostringstream out; out << L'/';
        for ( std::size_t i = 1; (i < path.size()); ++i ) {
            out << path[i] << L'/';
        }
        return (encode(out.str()));
    }

    w32::astring virtual_path
        ( const std::vector<w32::string>& path, const w32::string& name )
    {
        std::wostringstream out; out << L'/';
        for ( std::size_t i = 1; (i < path.size()); ++i ) {
            out << path[i] << L'/';
        }
        out << name;
        return (encode(out.str()));
    }

    bool requested_path
        ( std::istream& command, std::vector<w32::string>& path )
    {
        typedef std::char_traits<char> traits;
        
            // Use slash as a delimiter for easy compatibility with
            // UNIX-like clients: it is the most popular delimiter!
        static const traits::int_type slash = traits::to_int_type('/');
        
            // Handle absolute paths.
        if ( traits::eq_int_type(command.peek(),slash) ) {
            path.erase(path.begin()+1, path.end());
        }
        
            // Process each component separately.
        std::string component;
        while ( std::getline(command,component,'/') )
        {
            const w32::string name = decode(component.c_str());
            if ( name == L".." )
            {
                    // Don't allow access past the root.
                if ( path.size() <= 1 ) {
                    return (false);
                }
                path.pop_back();
            }
            else {
                path.push_back(name);
            }
        }
        
            // No error condition triggered!
        return (true);
    }

    template<typename Op>
    void listing ( const w32::string& path, Op process )
    {
        w32::fs::Search::Result result;
        w32::fs::Search search(path, result);
        do {
            if ( result.attributes().folder() ) {
                process("dir", result.name(), 0);
            }
            else {
                process("file", result.name(), result.size());
            }
        }
        while ( search.next(result) );
    }

        // Clean maching listing with specified format.
    class Mlsd
    {
        std::ostream& myOut;
    public:
        Mlsd ( std::ostream& out ) : myOut(out) {}
        void operator() ( const w32::astring& type,
            const w32::string& name, w32::qword size )
        {
            myOut << "type=" << type << ";size=" << size
                << "; " << encode(name) << "\r\n";
        }
    };

        // Name list. For automated clients that don't use MLSD.
    class Nlst
    {
        std::ostream& myOut;
    public:
        Nlst ( std::ostream& out ) : myOut(out) {}
        void operator() ( const w32::astring& type,
            const w32::string& name, w32::qword size )
        {
            myOut << encode(name) << "\r\n";
        }
    };

        // UNIX type hard listing.
    class List
    {
        std::ostream& myOut;
    public:
        List ( std::ostream& out ) : myOut(out) {}
        void operator() ( const w32::astring& type,
            const w32::string& name, w32::qword size )
        {
            std::string permissions("-rwxr--r--");
            if ( std::string(type.data()) == "dir" ) {
                 permissions[0] = 'd';
            }
            myOut << permissions << "   1 owner group "
                << std::left << std::setw(10) << size
                << "  " << encode(name) << "\r\n";
        }
    };

}

namespace ftp {

    class tolower
    {
        std::locale myLocale;
    public:
        tolower ( const std::locale& locale = std::locale() )
            : myLocale(locale)
        {}
        char operator() ( char x ) const {
            return (std::tolower(x, myLocale));
        }
    };

    std::istream& operator>>
        ( std::istream& in, w32::net::uint16& port )
    {
        return (in);
    }

    const std::string marker("\r\n");

    Service::Service ( server::Core& core )
        : server::Service(core), myHost(127,0,0,1), myPort(21)
    {
    }

    w32::uint16 Service::dynamicport ()
    {
            // Fair dice throw; guaranteed to be random.
        return (1234);
    }

    w32::io::OutputStream
        Service::uniquefile ( const Path& root, w32::string& name )
    {
             // Request failure upon conflict.
        const w32::io::OutputFile::Mode mode =
            w32::io::OutputFile::Mode::create();
        
            // Cryptographic provider required for random number generation.
        w32::cr::Provider provider(w32::cr::Provider::Type::ssl());
        while ( true )
        {
                // Generate a 40 hex-char long random name.
            name = w32::cr::convert(w32::cr::random(provider, 160));
            
                // Attempt to create a file with that name.
            try {
                const w32::string path = ::resolve_file(root,name);
                return (w32::io::OutputFile(path, mode));
            }
            catch ( const w32::Error& ) {}
        }
    }

    void Service::configure ( w32::xml::dom::Node node )
    {
            // Common service configuration.
        server::Service::configure(node);
        
        static const w32::bstring yes(L"yes");
        const w32::xml::dom::Attributes attributes = node.attributes();
        
            // Load the requested IP address.
        const w32::bstring ip = attributes.valueof(L"ip");
        myHost = w32::net::ipv4::Address(ip.data());
        
            // Change the default port when using TLS.
        const bool secure = (attributes(L"secure").value() == yes);
        if ( secure ) {
            myPort = 990;
        }
        
            // Allow use of non-default port.
        const w32::bstring port = attributes.valueof(L"port");
        if ( !port.empty() ) {
            std::wistringstream input(port.data());
            if ( !(input >> myPort) ) {
                // error...
            }
        }
        
            // Get reference to the accounts database.
        const w32::xml::dom::Node accounts = node.match(L"accounts");
        // ...
    }

    w32::net::ipv4::Address Service::host () const
    {
        return (myHost);
    }

    w32::uint16 Service::port () const
    {
        return (myPort);
    }

    server::Task * Service::connected ( Stream& stream, const Peer& peer )
    {
        return (new Control(*this, peer.address(), stream));
    }

    Control::Control ( Service& service,
        const w32::net::ipv4::Address& peer, w32::net::StreamSocket& stream )
        : Task(service), myPeer(peer), myStream(stream),
          myGBuf(8192,1024), myPBuf(8192,1024)
    {
        myStrategy.reset(new Active(peer, 20));
        myPath.push_back(w32::currentdirectory());
    }

    const w32::net::ipv4::Address& Control::peer () const
    {
        return (myPeer);
    }

    void Control::acquired ()
    {
            // Register for I/O completion notifications.
        core().bind(myStream, *this);
        
            // Send welcome message.
        reply(220, "eok.");
        
            // Prepare for input.
        myGBuf.get(myStream);
    }

    void Control::released ()
    {
            // No longer required.
        delete this;
    }

    void Control::abort ()
    {
    }

    void Control::completed
        ( const w32::io::Transfer * transfer, w32::dword size )
    {
    const w32::mt::CriticalSection::Lock _(myGuard);
        
            // Close session upon remote shutdown.
        if ( size == 0 ) {
            myStream.cancel();
            myStream.cancel();
            core().del(this); return;
        }
        
            // Acknowledge completion.
        if ( myGBuf.owns(*transfer) ) { myGBuf.did(size); }
        if ( myPBuf.owns(*transfer) ) { myPBuf.did(size); }
        
            // Process pending command(s).
        interpret();
        
            // Keep going!
        myGBuf.get(myStream);
        myPBuf.put(myStream);
    }

    void Control::interpret ()
    {
            // Find a terminating newline.
        static const w32::byte sentinel = static_cast<byte>('\n');
        const std::size_t size = myGBuf.peek(sentinel);
        if ( size == 0 ) {
            return;
        }
        
            // Fetch the command.
        std::string command(size, '\0');
        myGBuf.get(&command[0], size);
        command = command.substr(0, size-2);
        std::cout << "    >> '" << command << "'." << std::endl;
        
            // Split command name and arguments.
        std::istringstream query(command);
        std::string code; (query >> code).ignore(1);
        std::transform(code.begin(), code.end(), code.begin(), tolower());
        
                // Invoke the command's handler.
        dispatch(code, query);
    }

    void Control::reply ( int status, const std::string& message )
    {
        std::ostringstream response;
        response
            << std::setw(3) << std::setfill('0')
            << status << ' ' << message << marker;
        append(response.str());
        
            // Must keep transfering!
        myPBuf.put(myStream);
        myGBuf.get(myStream);
    }

    void Control::append ( const std::string& message )
    {
        myPBuf.put(message.data(), message.size());
        std::cout
            << "    << '" << message.substr(0, message.size()-2) << "'."
            << std::endl;
    }

    void Control::finished ()
    {
        reply(226, "eok."); core().del(myData.get()); myData.reset();
    }

    void Control::aborted ()
    {
        reply(426, "ecancelled."); core().del(myData.get()); myData.reset();
    }

    void Control::noop ( std::istream& command )
    {
        reply(200, "eok.");
    }

    void Control::help ( std::istream& command )
    {
        append("214-eok.\r\n");
        append(" <http://tools.ietf.org/html/rfc959>\r\n");
        append(" <http://tools.ietf.org/html/rfc2389>\r\n");
        append(" <http://tools.ietf.org/html/rfc2640>\r\n");
        append(" <http://tools.ietf.org/html/rfc3659>\r\n");
        reply(214, "eok.");
    }

    void Control::user ( std::istream& command )
    {
        std::getline(command, myUsername);
        if ( myUsername.empty() ) {
            reply(501, "einval."); return;
        }
        reply(331, "eok.");
    }

    void Control::pass ( std::istream& command )
    {
        std::string password; std::getline(command,password);
        /*myAccount = myServer.authenticate(myUsername, password);
        if ( myAccount.get() == 0 ) {
            reply(530, "enotconn."); return;
        }*/
        reply(230, "eok.");
    }

    void Control::acct ( std::istream& command )
    {
        reply(502, "enotavail.");
    }

    void Control::rein ( std::istream& command )
    {
        //myAccount.reset();
        reply(220, "eok.");
    }

    void Control::quit ( std::istream& command )
    {
        //myAccount.reset();
        //myDone = true;
        reply(221, "kthxbye.");
    }

    void Control::smnt ( std::istream& command )
    {
        reply(502, "enotavail.");
    }

    void Control::pwd ( std::istream& command )
    {
        std::ostringstream response;
        response
            << '"' << ::virtual_path(myPath)  << '"' << " eok.";
        reply(257, response.str());
    }

    void Control::cwd ( std::istream& command )
    {
            // Empty string is a protocol error.
        if ( command.eof() ) {
            reply(501, "einval."); return;
        }
        
            // Rollback on error!
        std::vector<w32::string> path = myPath;
        
            // Parse path and sanitize it.
        const bool safe = ::requested_path(command,path);
        if ( !safe ) {
            reply(550, "enoent."); return;
        }
        
            // Make sure the folder exists.
        if ( !w32::fs::Folder::is(::resolve_folder(path)) ) {
            reply(550, "enoent."); return;
        }
        
            // Commit path change.
        myPath.swap(path);
        reply(250, "eok.");
    }

    void Control::cdup ( std::istream& command )
    {
            // Don't allow access past the root.
        if ( myPath.size() == 1 ) {
            reply(550, "eaccess."); return;
        }
        myPath.pop_back();
        reply(250, "eok.");
    }

    void Control::pasv ( std::istream& command )
    {
        Service& myService = static_cast<Service&>(service());

            // Listen for incomming connection on dynamic port.
        const w32::net::ipv4::Address host = myService.host();
        const w32::uint16 port = myService.dynamicport();
        myStrategy.reset(new Passive(host, port));
        
            // Format client instructions.
        std::ostringstream response;
        response
            << "eok. ("
            << int(host._1())  << ',' << int(host._2()) << ','
            << int(host._3())  << ',' << int(host._4()) << ','
            << int(port / 256) << ',' << int(port % 256) << ')';
        reply(227, response.str());
    }

    void Control::port ( std::istream& command )
    {
            // Parse client instructions.
        w32::net::ipv4::Address host; w32::net::uint16 port;
        if (!(command >> host) || !(command >> port)) {
            reply(501, "einval.");
        }
        
            // Attempt connection.
        myStrategy.reset(new Active(host, port));
        
        reply(200, "eok.");
    }

    void Control::type ( std::istream& command )
    {
        std::string type; std::getline(command, type);
        if ((type != "A") && (type != "I")) {
            reply(504, "enosup.");
        }
        reply(200, "eok.");
    }

    void Control::stru ( std::istream& command )
    {
        std::string stru; std::getline(command, stru);
        if ( stru != "F" ) {
            reply(504, "enosup.");
        }
        reply(200, "eok.");
    }

    void Control::mode ( std::istream& command )
    {
        std::string mode; std::getline(command, mode);
        if ( mode != "S" ) {
            reply(504, "enosup.");
        }
        reply(200, "eok.");
    }

    void Control::retr ( std::istream& command )
    {
        //reply(450, "ebusy."); return;
        //reply(550, "enoent."); return;
        
            // Empty path is a protocol error.
        if ( command.eof() ) {
            reply(501, "einval."); return;
        }
        
            // Parse path and sanitize it.
        std::vector<w32::string> path = myPath;
        const bool safe = ::requested_path(command,path);
        if ( !safe ) {
            reply(550, "enoent."); return;
        }
        std::cout
            << ::resolve_file(path) << std::endl;
        
            // Open the requested file.
        w32::io::InputFile file(::resolve_file(path));
        
            // Get data connection.
        myData.reset(new Data(*this, myStrategy->complete()));
        myStrategy.reset(new Active(myPeer, 20));
        
            // Start transfer.
        core().add(myData.get());
        myData->download(file);
        
            // Indicate start of transfer.
        reply(150, "einprogress.");
    }

    void Control::allo ( std::istream& command )
    {
            // Could be implemented, but is difficult to implement
            // when followed by APPE... what does RFC959 suggest?
        reply(202, "eok.");
    }

    void Control::stor ( std::istream& command )
    {
        //reply(532, "eperm.");
        
            // Empty path is a protocol error.
        if ( command.eof() ) {
            reply(501, "einval."); return;
        }
        
            // Parse path and sanitize it.
        std::vector<w32::string> path = myPath;
        const bool safe = ::requested_path(command,path);
        if ( !safe ) {
            reply(550, "enoent."); return;
        }
        
            // Open the requested file.
        w32::io::OutputFile file(::resolve_file(path));
        
            // Get data connection.
        myData.reset(new Data(*this, myStrategy->complete()));
        myStrategy.reset(new Active(myPeer, 20));
        
            // Start transfer.
        core().add(myData.get());
        myData->upload(file);
        
            // Indicate start of transfer.
        reply(150, "einprogress.");
    }

    void Control::stou ( std::istream& command )
    {
        Service& myService = static_cast<Service&>(service());
        //reply(532, "eperm.");
        
            // Get a file with a unique name.
        w32::string name;
        w32::io::OutputStream file = myService.uniquefile(myPath, name);
        
            // Get data connection.
        w32::net::tcp::Stream stream = myStrategy->complete();
        myStrategy.reset(new Active(myPeer, 20));
        
            // Start transfer.
        core().add(myData.get());
        myData->upload(file);
        
            // Indicate start of transfer.
        reply(150, "einprogress.");
    }

    void Control::appe ( std::istream& command )
    {
        reply(502, "enotavail."); return;
        
            // Empty path is a protocol error.
        if ( command.eof() ) {
            reply(501, "einval."); return;
        }
        
            // Parse path and sanitize it.
        std::vector<w32::string> path = myPath;
        const bool safe = ::requested_path(command,path);
        if ( !safe ) {
            reply(550, "enoent."); return;
        }
        
            // Prepare for upload.
        w32::io::OutputFile file(::resolve_file(path),
            w32::io::OutputFile::Mode::append());
        
            // Get data connection.
        w32::net::tcp::Stream stream = myStrategy->complete();
        myStrategy.reset(new Active(myPeer, 20));
        
            // Start transfer.
        core().add(myData.get());
        myData->upload(file);
        
            // Indicate start of transfer.
        reply(150, "einprogress.");
    }

    void Control::abor ( std::istream& command )
    {
            // Abort the transfer without closing the data connection
            // when the mode is not 'S' (stream).
        if ( myData.get() ) {
            //myData->abort();
        }
        reply(226, "eok.");
    }

    void Control::rest ( std::istream& command )
    {
        //reply(350, "eok.");
        reply(502, "enotavail.");
    }

    void Control::rnfr ( std::istream& command )
    {
        //reply(350, "eok.");
        reply(502, "enotavail.");
    }

    void Control::rnto ( std::istream& command )
    {
        //reply(250, "eok.");
        reply(502, "enotavail.");
    }

    void Control::dele ( std::istream& command )
    {
        reply(502, "enotavail."); return;
        
            // Empty path is a protocol error.
        if ( command.eof() ) {
            reply(501, "einval."); return;
        }
        
            // Parse path and sanitize it.
        std::vector<w32::string> path = myPath;
        const bool safe = ::requested_path(command,path);
        if ( !safe ) {
            reply(550, "enoent."); return;
        }
        
            // Proceed.
        w32::fs::unlink(::resolve_file(path));
        reply(250, "eok.");
    }

    void Control::rmd ( std::istream& command )
    {
        reply(502, "enotavail."); return;
        
            // Empty path is a protocol error.
        if ( command.eof() ) {
            reply(501, "einval."); return;
        }
        
            // Parse path and sanitize it.
        std::vector<w32::string> path = myPath;
        const bool safe = ::requested_path(command,path);
        if ( !safe ) {
            reply(550, "enoent."); return;
        }
        
            // Proceed.
        w32::fs::unlink(::resolve_folder(path));
        reply(250, "eok.");
    }

    void Control::mkd ( std::istream& command )
    {
        //reply(521, "eexist.");
        
            // Empty path is a protocol error.
        if ( command.eof() ) {
            reply(501, "einval."); return;
        }
        
            // Parse path and sanitize it.
        std::vector<w32::string> path = myPath;
        const bool safe = ::requested_path(command,path);
        if ( !safe ) {
            reply(550, "enoent."); return;
        }
        
            // Proceed.
        w32::fs::Folder::create(::resolve_folder(path));
        std::ostringstream response;
        response
            << "\"" << ::virtual_path(path) << "/\" eok.";
        reply(257, response.str());
    }

    void Control::list ( std::istream& command )
    {
            // Get data connection.
        w32::net::tcp::Stream stream = myStrategy->complete();
        myStrategy.reset(new Active(myPeer, 20));
        
            // Indicate start of transfer.
        reply(150, "einprogress.");
        
            // Transfer folder listing.
        w32::net::streambuf buffer(stream);
        std::ostream out(&buffer);
        
            // Generate listing.
        ::listing(::search_pattern(myPath), List(out));
        
            // Finish sending listing.
        out << std::flush;
        
            // Indicate end of transfer.
        reply(226, "eok.");
    }

    void Control::nlst ( std::istream& command )
    {
            // Get data connection.
        w32::net::tcp::Stream stream = myStrategy->complete();
        myStrategy.reset(new Active(myPeer, 20));
        
            // Indicate start of transfer.
        reply(150, "einprogress.");
        
            // Transfer folder listing.
        w32::net::streambuf buffer(stream);
        std::ostream out(&buffer);
        
            // Generate listing.
        ::listing(::search_pattern(myPath), Nlst(out));
        
            // Finish sending listing.
        out << std::flush;
        
            // Indicate end of transfer.
        reply(226, "eok.");
    }

    void Control::site ( std::istream& command )
    {
        reply(502, "enotavail.");
    }

    void Control::syst ( std::istream& command )
    {
        reply(215, "WINDOWS-NT-6 ...");
    }

    void Control::stat ( std::istream& command )
    {
        reply(502, "enotavail.");
    }

    void Control::feat ( std::istream& command )
    {
        append("211-eok.\r\n");
        append(" UTF8\r\n");
        append(" MLST type*;size*;\r\n");
        append(" MLSD\r\n");
        append("211 eok.\r\n");
    }

    void Control::opts ( std::istream& command )
    {
        reply(200, "eok.");
    }

    void Control::mlsd ( std::istream& command )
    {
            // Get data connection.
        w32::net::tcp::Stream stream = myStrategy->complete();
        myStrategy.reset(new Active(myPeer, 20));
        
            // Indicate start of transfer.
        reply(150, "einprogress.");
        
            // Transfer folder listing.
        w32::net::streambuf buffer(stream);
        std::ostream out(&buffer);
        
            // Generate listing.
        ::listing(::search_pattern(myPath), Mlsd(out));
        
            // Finish sending listing.
        out << std::flush;
        
            // Indicate end of transfer.
        reply(226, "eok.");
    }

    template<typename T>
    class first_equals
    {
        T my1st;
    public:
        first_equals ( const T& first )
            : my1st(first)
        {}
        template<typename U> bool operator()
            ( const std::pair<T,U>& x ) const
        {
            return (x.first == my1st);
        }
    };

    void Control::dispatch
        ( const std::string& code, std::istream& query )
    {
        typedef void(Control::*handler)(std::istream& arguments);
        typedef std::pair<std::string, handler> command;
        typedef const command * command_iterator;
        static const command commands[] = {
                // <http://tools.ietf.org/html/rfc959>.
            command("noop", &Control::noop),
            command("help", &Control::help),
            command("user", &Control::user),
            command("pass", &Control::pass),
            command("acct", &Control::acct),
            command("rein", &Control::rein),
            command("quit", &Control::quit),
            command("smnt", &Control::smnt),
            command("pwd" , &Control::pwd ),
            command("cwd" , &Control::cwd ),
            command("cdup", &Control::cdup),
            command("pasv", &Control::pasv),
            command("port", &Control::port),
            command("type", &Control::type),
            command("stru", &Control::stru),
            command("mode", &Control::mode),
            command("retr", &Control::retr),
            command("stor", &Control::stor),
            command("stou", &Control::stou),
            command("appe", &Control::appe),
            command("allo", &Control::allo),
            command("rest", &Control::rest),
            command("rnfr", &Control::rnfr),
            command("rnto", &Control::rnto),
            command("abor", &Control::abor),
            command("dele", &Control::dele),
            command("rmd" , &Control::rmd ),
            command("mkd" , &Control::mkd ),
            command("list", &Control::list),
            command("nlst", &Control::nlst),
            command("site", &Control::site),
            command("syst", &Control::syst),
            
                // <http://tools.ietf.org/html/rfc2389>.
            command("feat", &Control::feat),
            command("opts", &Control::opts),
            
                // <http://tools.ietf.org/html/rfc2640>.
            //command("lang", &Control::lang),
            
                // <http://tools.ietf.org/html/rfc3659>.
            //command("mdtm", &Control::mdtm),
            //command("size", &Control::size),
            //command("tvfs", &Control::tvfs),
            //command("mlst", &Control::mlst),
            command("mlsd", &Control::mlsd),
        };
        static const std::size_t count =
            sizeof(commands) / sizeof(command);
        static const command_iterator begin = commands;
        static const command_iterator end = begin + count;
        
            // Look for a matching command.
        const command_iterator match = std::find_if(
            begin, end, first_equals<std::string>(code));
        if ( match == end )
        {
            std::cerr
                << "  (( unknown command: '" << code << "'. ))"
                << std::endl;
            reply(500, "eproto."); return;
        }
        
            // Invoke it.
        try {
            (this->*(match->second))(query);
        }
        catch ( const w32::Error& error ) {
            std::cerr
                << "  (( error: '" << error << ".'! ))" << std::endl;
            reply(451, "efault."); return;
        }
        catch ( ... ) {
            reply(451, "efault."); return;
        }
    }

    Transfer::Transfer ()
        : myGBuf(8192,1024), myPBuf(8192,1024)
    {
    }

    Transfer::~Transfer ()
    {
    }

    bool Transfer::completed
        ( const w32::io::Transfer& transfer, w32::dword size )
    {
            // Acknowledge completion.
        if ( myGBuf.owns(transfer) ) { myGBuf.did(size); }
        if ( myPBuf.owns(transfer) ) { myPBuf.did(size); }
        
            // Derived class knows the real answer.
        return (false);
    }

    Upload::Upload ( w32::io::OutputStream& file )
        : myFile(file)
    {
    }

    void Upload::haul ( w32::net::StreamSocket& stream )
    {
            // Move data to output buffers.
        myPBuf << myGBuf;
        
            // Start new transfers.
        myGBuf.get(stream);
        myPBuf.put(myFile);
    }

    bool Upload::completed
        ( const w32::io::Transfer& transfer, w32::dword size )
    {
            // Ask base class to adjust buffers.
        Transfer::completed(transfer,size);
        
            // Not quite sure this always works!
        return (myPBuf.owns(transfer) && (size < 1024));
    }

    Upload::~Upload ()
    {
            // Make sure we don't receive any more notifications.
        myFile.cancel();
    }

    Download::Download ( w32::io::InputStream& file )
        : myFile(file)
    {
    }

    Download::~Download ()
    {
            // Make sure we don't receive any more notifications.
        myFile.cancel();
    }

    void Download::haul ( w32::net::StreamSocket& stream )
    {
            // Move data to output buffers.
        myPBuf << myGBuf;
        
            // Start new transfers.
        myGBuf.get(myFile);
        myPBuf.put(stream);
    }

    bool Download::completed
        ( const w32::io::Transfer& transfer, w32::dword size )
    {
            // Ask base class to adjust buffers.
        Transfer::completed(transfer,size);
        
            // Not quite sure this always works!
        return (myPBuf.owns(transfer) && (size < 1024));
    }

    Data::Data ( Control& control, w32::net::StreamSocket& stream )
        : Task(control.service()), myControl(control), myStream(stream)
    {
    }

    void Data::acquired ()
    {
            // Register for I/O completion notifications.
        core().bind(myStream, *this);
    }

    void Data::released ()
    {
        myTransfer.reset();
    }

    void Data::abort ()
    {
        myControl.aborted();
    }

    void Data::download ( w32::io::InputStream& file )
    {
        myTransfer.reset(new Download(file)); core().bind(file, *this);
        
            // Initiate transfers!
        myTransfer->haul(myStream);
    }

    void Data::upload ( w32::io::OutputStream& file )
    {
        myTransfer.reset(new Upload(file)); core().bind(file, *this);
        
            // Initiate transfers!
        myTransfer->haul(myStream);
    }

    void Data::completed
        ( const w32::io::Transfer * transfer, w32::dword size )
    {
    const w32::mt::CriticalSection::Lock _(myGuard);
        
            // Acknowledge completion & check for end.
        if ( myTransfer->completed(*transfer,size) )
        {
            myControl.finished(); /*done(true);*/ return;
        }
        
            // Keep transferring.
        myTransfer->haul(myStream);
    }

}
