#ifndef _ftp_Strategy_hpp__
#define _ftp_Strategy_hpp__

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

#include <w32.net.hpp>
#include <memory>

namespace ftp {

    class Service;
    class Control;

    class Strategy
    {
        /* construction. */
    public:
        virtual ~Strategy ();

        /* methods. */
    public:
        virtual w32::net::tcp::Stream complete () = 0;
    };

    class Passive :
        public Strategy
    {
        /* data. */
    private:
        w32::net::ipv4::EndPoint myHost;
        w32::net::tcp::Listener myListener;

        /* construction. */
    public:
        explicit Passive ( const w32::net::ipv4::EndPoint& host );
        Passive ( const w32::net::ipv4::Address& host, w32::net::uint16 port );

        /* overrides. */
    public:
        virtual w32::net::tcp::Stream complete ();
    };

    class Active :
        public Strategy
    {
        /* data. */
    private:
        w32::net::ipv4::EndPoint myPeer;

        /* construction. */
    public:
        explicit Active ( const w32::net::ipv4::EndPoint& peer );
        Active ( const w32::net::ipv4::Address& host, w32::net::uint16 port );

        /* overrides. */
    public:
        virtual w32::net::tcp::Stream complete ();
    };

}

#endif /* _ftp_Strategy_hpp__ */
