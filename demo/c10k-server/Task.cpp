// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Task.hpp"
#include "Core.hpp"
#include "Service.hpp"
#include <iostream>

namespace server {

    Task::Task ( Service& service )
        : myService(service)
    {
        core().add(this);
    }

    Task::~Task ()
    {
        core().del(this);
        std::cout << "  (( task completed. ))\n";
    }

    void Task::acquired ()
    {
    }

    void Task::released ()
    {
    }

    Service& Task::service ()
    {
        return (myService);
    }

    Core& Task::core ()
    {
        return (service().core());
    }

}
