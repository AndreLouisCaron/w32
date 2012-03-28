#ifndef _echo_Service_hpp__
#define _echo_Service_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../Service.hpp"
#include "Task.hpp"

namespace echo {

    class Service :
        public server::Service
    {
        /* construction. */
    public:
        Service ( server::Core& core );

        /* overrides. */
    public:
        virtual w32::uint16 port () const;
        virtual Task * connected ( Stream& stream, const Peer& peer );
    };

}

#endif /* _echo_Service_hpp__ */
