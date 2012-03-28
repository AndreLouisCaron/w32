// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Service.hpp"
#include "Task.hpp"

namespace echo {

    Service::Service ( server::Core& core )
        : server::Service(core)
    {
    }

    w32::uint16 Service::port () const
    {
        return (4321);
    }

    Task * Service::connected ( Stream& stream, const Peer& peer )
    {
        return (new Task(*this, stream));
    }

}
