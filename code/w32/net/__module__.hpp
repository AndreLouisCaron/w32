#ifndef _w32_net_hpp__
#define _w32_net_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 {
    namespace net {}
}

#include "../__compiler-intro__.hpp"
#   include <w32/net/Buffer.hpp>
#   include <w32/net/Context.hpp>
#   include <w32/net/Event.hpp>
#   include <w32/net/Host.hpp>
#   include <w32/net/integers.hpp>
#   include <w32/net/select.hpp>
#   include <w32/net/Set.hpp>
#   include <w32/net/sockstream.hpp>
#   include <w32/net/Timespan.hpp>
#   include <w32/net/ipv4/Address.hpp>
#   include <w32/net/ipv4/EndPoint.hpp>
#   include <w32/net/ipv6/Address.hpp>
#   include <w32/net/tcp/Listener.hpp>
#   include <w32/net/tcp/Stream.hpp>
#include "../__compiler-outro__.hpp"

#endif /* _w32_net_hpp__ */
