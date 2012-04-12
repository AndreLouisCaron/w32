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
#include <iostream>
#include <sstream>

namespace ftp {

    std::string& welcome::message ()
    {
        return (myMessage);
    }

    const std::string& welcome::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const welcome& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::istream& in, welcome& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        do {
            if ( !std::getline(in,reply,'\r') || !in.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "220", 3) != 0 ); }
        
        out.message() = message.str();
        return (in);
    }

    login::login ( const std::string& user, const std::string& pass )
        : myUser(user), myPass(pass)
    {
    }

    std::string& login::user ()
    {
        return (myUser);
    }

    const std::string& login::user () const
    {
        return (myUser);
    }

    std::string& login::pass ()
    {
        return (myPass);
    }

    const std::string& login::pass () const
    {
        return (myPass);
    }

    std::string& login::message ()
    {
        return (myMessage);
    }

    const std::string& login::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const login& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::iostream& io, login& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        io << "user " << out.user() << "\r\n" << std::flush
           << "pass " << out.pass() << "\r\n" << std::flush;
        do {
            if ( !std::getline(io,reply,'\r') || !io.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "230 ", 4) != 0 ); }
        
        out.message() = message.str();
        return (io);
    }

    std::string& syst::message ()
    {
        return (myMessage);
    }

    const std::string& syst::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const syst& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::iostream& io, syst& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        io << "syst" << std::endl;
        do {
            if ( !std::getline(io,reply,'\r') || !io.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "215", 3) != 0 ); }
        
        out.message() = message.str();
        return (io);
    }

    std::string& stat::message ()
    {
        return (myMessage);
    }

    const std::string& stat::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const stat& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::iostream& io, stat& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        io << "stat" << std::endl;
        do {
            if ( !std::getline(io,reply,'\r') || !io.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "211", 3) != 0 ); }
        
        out.message() = message.str();
        return (io);
    }

    std::string& pasv::message ()
    {
        return (myMessage);
    }

    const std::string& pasv::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const pasv& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::iostream& io, pasv& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        io << "pasv" << std::endl;
        do {
            if ( !std::getline(io,reply,'\r') || !io.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "227", 3) != 0 ); }
        
        out.message() = message.str();
        return (io);
    }

    std::string& pwd::message ()
    {
        return (myMessage);
    }

    const std::string& pwd::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const pwd& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::iostream& io, pwd& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        io << "pwd" << std::endl;
        do {
            if ( !std::getline(io,reply,'\r') || !io.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "257", 3) != 0 ); }
        
        out.message() = message.str();
        return (io);
    }

    cwd::cwd ( const std::string& path )
        : myPath(path)
    {
    }

    std::string& cwd::path ()
    {
        return (myPath);
    }

    const std::string& cwd::path () const
    {
        return (myPath);
    }

    std::string& cwd::message ()
    {
        return (myMessage);
    }

    const std::string& cwd::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const cwd& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::iostream& io, cwd& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        io << "cwd " << out.path() << std::endl;
        do {
            if ( !std::getline(io,reply,'\r') || !io.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "250", 3) != 0 ); }
        
        out.message() = message.str();
        return (io);
    }

    std::string& quit::message ()
    {
        return (myMessage);
    }

    const std::string& quit::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const quit& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::iostream& io, quit& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        io << "quit" << std::endl;
        do {
            if ( !std::getline(io,reply,'\r') || !io.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "221", 3) != 0 ); }
        
        out.message() = message.str();
        return (io);
    }

    std::string& list::message ()
    {
        return (myMessage);
    }

    const std::string& list::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const list& in )
    {
        return (out << in.message());
    }

    void list::operator()
        ( std::iostream& control, std::istream& in, std::ostream& out )
    {
        myMessage.clear();
        
        std::ostringstream message;
        { std::string reply;
        control << "list" << std::endl;
        do {
            if ( !std::getline(control,reply,'\r') || !control.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            out << in.rdbuf();
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "150", 3) != 0 ); }
        
        myMessage = message.str();
    }

    std::string& nlst::message ()
    {
        return (myMessage);
    }

    const std::string& nlst::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const nlst& in )
    {
        return (out << in.message());
    }

    void nlst::operator()
        ( std::iostream& control, std::istream& in, std::ostream& out )
    {
        myMessage.clear();
        
        std::ostringstream message;
        { std::string reply;
        control << "nlst" << std::endl;
        do {
            if ( !std::getline(control,reply,'\r') || !control.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            out << in.rdbuf();
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "150", 3) != 0 ); }
        
        myMessage = message.str();
    }

    type::type ( char code )
        : myCode(code)
    {
    }

    char& type::code ()
    {
        return (myCode);
    }

    char type::code () const
    {
        return (myCode);
    }

    std::string& type::message ()
    {
        return (myMessage);
    }

    const std::string& type::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const type& in )
    {
        return (out << in.message());
    }

    std::istream& operator>> ( std::iostream& io, type& out )
    {
        out.message().clear();
        
        std::ostringstream message;
        { std::string reply;
        io << "type " << out.code() << std::endl;
        do {
            if ( !std::getline(io,reply,'\r') || !io.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "200", 3) != 0 ); }
        
        out.message() = message.str();
        return (io);
    }

    retr::retr ( const std::string& path )
        : myPath(path)
    {
    }

    std::string& retr::path ()
    {
        return (myPath);
    }

    const std::string& retr::path () const
    {
        return (myPath);
    }

    std::string& retr::message ()
    {
        return (myMessage);
    }

    const std::string& retr::message () const
    {
        return (myMessage);
    }

    std::ostream& operator<< ( std::ostream& out, const retr& in )
    {
        return (out << in.message());
    }

    void retr::operator()
        ( std::iostream& control, std::istream& in, std::ostream& out )
    {
        myMessage.clear();
        
        std::ostringstream message;
        { std::string reply;
        control << "retr " << myPath << std::endl;
        do {
            if ( !std::getline(control,reply,'\r') || !control.ignore(1) ) {
                throw (std::exception("connection killed!"));
            }
            //std::cerr << "'" << reply << "'" << std::endl;
            for ( std::string _; (std::getline(in,_)); ) {
                out << in << std::endl;
            }
            message << reply << std::endl;
        }
        while ( std::strncmp(reply.c_str(), "150", 3) != 0 ); }
        
        myMessage = message.str();
    }

}
