#ifndef _server_Service_hpp__
#define _server_Service_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
