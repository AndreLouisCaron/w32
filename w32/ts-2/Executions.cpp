// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-2/Executions.hpp>
#include <w32/ts-2/Service.hpp>

namespace {

    ::IRunningTaskCollection * fetch ( ::ITaskService * service )
    {
        ::IRunningTaskCollection * tasks = 0;
        const w32::com::Result result = service->GetRunningTasks(0, &tasks);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService, GetRunningTasks, result);
        }
        return (tasks);
    }

    ::IRunningTaskCollection * fetch ( ::IRegisteredTask * task )
    {
        ::IRunningTaskCollection * tasks = 0;
        const w32::com::Result result = task->GetInstances(0, &tasks);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask, GetInstances, result);
        }
        return (tasks);
    }

}

namespace w32 { namespace ts {

    Executions::Executions ( Service& service )
        : com::Wrapper< ::IRunningTaskCollection >
              ( ::fetch(service.ptr().value()) )
    {
    }

    long Executions::count () const
    {
        long value = 0;
        const com::Result result = ptr()->get_Count(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTaskCollection, get_Count, result);
        }
        return (value);
    }

} }
