#ifndef _server_Service_hpp__
#define _server_Service_hpp__

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
#include <w32.xml.hpp>

namespace server {

    class Core;
    class Task;

    class Service
    {
    friend class Core;

        /* nested types. */
    public:
        typedef w32::net::tcp::Stream Stream;
        typedef w32::net::ipv4::EndPoint Peer;

        /* data. */
    private:
        Core& myCore;

        /* construction. */
    public:
        Service ( Core& core );
        virtual ~Service ();

        /* methods. */
    public:
        virtual void configure ( w32::xml::dom::Node node );

        virtual void acquired ();
        virtual void released ();
        Core& core ();

        virtual w32::uint16 port () const = 0;
        virtual void shutdown ();
        virtual Task * connected ( Stream& stream, const Peer& peer ) = 0;
    };

}

#endif /* _server_Service_hpp__ */
