#ifndef _ftp_hpp__
#define _ftp_hpp__

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

#include <iosfwd>
#include <string>

namespace ftp {

    class welcome
    {
        std::string myMessage;
    public:
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const welcome& in );
    std::istream& operator>> ( std::istream& in, welcome& out );

    class login
    {
        std::string myUser;
        std::string myPass;
        std::string myMessage;
    public:
        login ( const std::string& user, const std::string& pass );
        std::string& user ();
        const std::string& user () const;
        std::string& pass ();
        const std::string& pass () const;
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const login& in );
    std::istream& operator>> ( std::iostream& io, login& out );

    class syst
    {
        std::string myMessage;
    public:
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const syst& in );
    std::istream& operator>> ( std::iostream& io, syst& out );

    class stat
    {
        std::string myMessage;
    public:
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const stat& in );
    std::istream& operator>> ( std::iostream& io, stat& out );

    class pasv
    {
        std::string myMessage;
    public:
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const pasv& in );
    std::istream& operator>> ( std::iostream& io, pasv& out );

    class pwd
    {
        std::string myMessage;
    public:
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const pwd& in );
    std::istream& operator>> ( std::iostream& io, pwd& out );

    class cwd
    {
        std::string myPath;
        std::string myMessage;
    public:
        cwd ( const std::string& path );
        std::string& path ();
        const std::string& path () const;
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const cwd& in );
    std::istream& operator>> ( std::iostream& io, cwd& out );

    class quit
    {
        std::string myMessage;
    public:
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const quit& in );
    std::istream& operator>> ( std::iostream& io, quit& out );

    class list
    {
        std::string myMessage;
    public:
        std::string& message ();
        const std::string& message () const;
        void operator() ( std::iostream& control, std::istream& in, std::ostream& out );
    };
    std::ostream& operator<< ( std::ostream& out, const list& in );

    class nlst
    {
        std::string myMessage;
    public:
        std::string& message ();
        const std::string& message () const;
        void operator() ( std::iostream& control, std::istream& in, std::ostream& out );
    };
    std::ostream& operator<< ( std::ostream& out, const nlst& in );

    class type
    {
        char myCode;
        std::string myMessage;
    public:
        type ( char code );
        char& code ();
        char code () const;
        std::string& message ();
        const std::string& message () const;
    };
    std::ostream& operator<< ( std::ostream& out, const type& in );
    std::istream& operator>> ( std::iostream& io, type& out );

    class retr
    {
        std::string myPath;
        std::string myMessage;
    public:
        retr ( const std::string& path );
        std::string& path ();
        const std::string& path () const;
        std::string& message ();
        const std::string& message () const;
        void operator() ( std::iostream& control, std::istream& in, std::ostream& out );
    };
    std::ostream& operator<< ( std::ostream& out, const retr& in );

}

#endif /* _ftp_hpp__ */
