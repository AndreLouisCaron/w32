#ifndef _ftp_Strategy_hpp__
#define _ftp_Strategy_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
