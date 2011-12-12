#ifndef _w32_net_select_hpp__
#define _w32_net_select_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.net/Context.hpp>
#include <w32.net/Set.hpp>
#include <w32.net/Timespan.hpp>

namespace w32 { namespace net {

    void select
        ( Set& read, Set& write, Set& errors );

    bool select
        ( Set& read, Set& write, Set& errors, const Timespan& timeout );

    void select ( Set& sockets );
    bool select
        ( Set& sockets, const Timespan& timeout );

    bool readable ( const Socket& socket );
    bool readable
        ( const Socket& socket, const Timespan& timeout );
    bool writable ( const Socket& socket );

} }

#endif /*  _w32_net_select_hpp__ */
