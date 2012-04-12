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

#include "../Core.hpp"
#include "../Service.hpp"
#include "../Task.hpp"
#include "../Buffer.hpp"
#include <istream>
#include <map>
#include <vector>

namespace ftp {

    class Control;
    class Data;
    class Strategy;

    typedef std::vector<w32::string> Path;

    class Service :
        public server::Service
    {
        /* data. */
    private:
        w32::net::ipv4::Address myHost;
        w32::uint16 myPort;

        /* construction. */
    public:
        Service ( server::Core& core );

        /* methods. */
    public:
        w32::uint16 dynamicport ();
        w32::io::OutputStream
            uniquefile ( const Path& path, w32::string& name );

        /* overrides. */
    public:
        virtual void configure ( w32::xml::dom::Node node );
        virtual w32::net::ipv4::Address host () const;
        virtual w32::uint16 port () const;
        virtual server::Task *
            connected ( Stream& stream, const Peer& peer );
    };

    class Control :
        public server::Task
    {
        /* data. */
    protected:
            // I/O operations.
        w32::net::ipv4::Address myPeer;
        w32::net::StreamSocket myStream;
        server::IBuffer myGBuf;
        server::OBuffer myPBuf;

            // Thread-safety.
        w32::mt::CriticalSection myGuard;

            // Session state.
        std::string myUsername;
        std::vector<w32::string> myPath;

            // Data connection management.
        std::auto_ptr<Data> myData;
        std::auto_ptr<Strategy> myStrategy;

        /* construction. */
    public:
        Control ( Service& service, const w32::net::ipv4::Address& peer,
            w32::net::StreamSocket& stream );

        /* methods. */
    public:
        const w32::net::ipv4::Address& peer () const;

            // Status updates from data connection.
        void finished ();
        void aborted ();

    private:
        void interpret ();
        void reply ( int status,
            const std::string& message = std::string() );
        void append ( const std::string& message = std::string() );
        void dispatch
            ( const std::string& code, std::istream& query );

        /* overrides. */
    public:
        virtual void acquired ();
        virtual void released ();

        virtual void abort ();
        virtual void completed
            ( const w32::io::Transfer * transfer, w32::dword size );

        /* methods. */
    private:
            // <http://tools.ietf.org/html/rfc959>.
        void noop ( std::istream& command );
        void help ( std::istream& command );
        void user ( std::istream& command );
        void pass ( std::istream& command );
        void acct ( std::istream& command );
        void rein ( std::istream& command );
        void quit ( std::istream& command );
        void smnt ( std::istream& command );
        void pwd  ( std::istream& command );
        void cwd  ( std::istream& command );
        void cdup ( std::istream& command );
        void pasv ( std::istream& command );
        void port ( std::istream& command );
        void type ( std::istream& command );
        void stru ( std::istream& command );
        void mode ( std::istream& command );
        void retr ( std::istream& command );
        void stor ( std::istream& command );
        void stou ( std::istream& command );
        void appe ( std::istream& command );
        void allo ( std::istream& command );
        void rest ( std::istream& command );
        void rnfr ( std::istream& command );
        void rnto ( std::istream& command );
        void abor ( std::istream& command );
        void dele ( std::istream& command );
        void rmd  ( std::istream& command );
        void mkd  ( std::istream& command );
        void list ( std::istream& command );
        void nlst ( std::istream& command );
        void site ( std::istream& command );
        void syst ( std::istream& command );
        void stat ( std::istream& command );

            // <http://tools.ietf.org/html/rfc2389>.
        void feat ( std::istream& command );
        void opts ( std::istream& command );

            // <http://tools.ietf.org/html/rfc2640>.
        void lang ( std::istream& command );

            // <http://tools.ietf.org/html/rfc3659>.
        void mdtm ( std::istream& command );
        void size ( std::istream& command );
        void tvfs ( std::istream& command );
        void mlst ( std::istream& command );
        void mlsd ( std::istream& command );
    };

    class Transfer
    {
        /* data. */
    protected:
        server::IBuffer myGBuf;
        server::OBuffer myPBuf;

        /* construction. */
    public:
        Transfer ();
        virtual ~Transfer ();

        /* methods. */
    public:
        virtual bool completed
            ( const w32::io::Transfer& transfer, w32::dword size );
        virtual void haul ( w32::net::StreamSocket& socket ) = 0;
    };

    class Upload :
        public Transfer
    {
        /* data. */
    private:
        w32::io::OutputStream myFile;

        /* construction. */
    public:
        Upload ( w32::io::OutputStream& file );
        virtual ~Upload ();

        /* overrides. */
    public:
        virtual bool completed
            ( const w32::io::Transfer& transfer, w32::dword size );
        virtual void haul ( w32::net::StreamSocket& stream );
    };

    class Download :
        public Transfer
    {
        /* data. */
    private:
        w32::io::InputStream myFile;

        /* construction. */
    public:
        Download ( w32::io::InputStream& file );
        virtual ~Download ();

        /* overrides. */
    public:
        virtual bool completed
            ( const w32::io::Transfer& transfer, w32::dword size );
        virtual void haul ( w32::net::StreamSocket& stream );
    };

    class Data :
        public server::Task
    {
        /* data. */
    private:
        Control& myControl;
        w32::net::StreamSocket myStream;
        w32::mt::CriticalSection myGuard;
        std::auto_ptr<Transfer> myTransfer;

        /* construction. */
    public:
        Data ( Control& control, w32::net::StreamSocket& stream );

        /* methods. */
    public:
        void download ( w32::io::InputStream& file );
        void upload ( w32::io::OutputStream& file );

        /* overrides. */
    public:
        virtual void acquired ();
        virtual void released ();

        virtual void abort ();
        virtual void completed
            ( const w32::io::Transfer * transfer, w32::dword size );
    };

}

#endif /* _ftp_hpp__ */
