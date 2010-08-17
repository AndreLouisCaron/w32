#ifndef _ftp_hpp__
#define _ftp_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
