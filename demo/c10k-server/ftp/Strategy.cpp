// Copyright(c) Andre Caron, 2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Strategy.hpp"
#include "ftp.hpp"

namespace ftp {

    Strategy::~Strategy ()
    {
    }

    Passive::Passive ( const w32::net::ipv4::EndPoint& host )
        : myHost(host), myListener(myHost)
    {
    }

    Passive::Passive (
        const w32::net::ipv4::Address& host, w32::net::uint16 port )
        : myHost(host, port), myListener(myHost)
    {
    }

    w32::net::tcp::Stream Passive::complete ()
    {
        return (w32::net::tcp::Stream(myListener));
    }

    Active::Active ( const w32::net::ipv4::EndPoint& peer )
        : myPeer(peer)
    {
    }

    Active::Active (
        const w32::net::ipv4::Address& host, w32::net::uint16 port )
        : myPeer(host, port)
    {
    }

    w32::net::tcp::Stream Active::complete ()
    {
        return (w32::net::tcp::Stream(myPeer));
    }

}
