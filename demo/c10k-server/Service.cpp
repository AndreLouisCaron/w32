// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Service.hpp"

namespace server {

    Service::Service ( Core& core )
        : myCore(core)
    {
    }

    Service::~Service ()
    {
    }

    void Service::configure ( w32::xml::dom::Node node )
    {
    }

    void Service::shutdown ()
    {
    }

    void Service::acquired ()
    {
    }

    void Service::released ()
    {
    }

    Core& Service::core ()
    {
        return (myCore);
    }

}
