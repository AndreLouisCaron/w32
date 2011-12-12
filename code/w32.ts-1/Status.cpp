// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ts-1/Status.hpp>
#include <w32.ts-1/Task.hpp>

namespace {

    ::HRESULT query ( ::ITask * task )
    {
        ::HRESULT status = 0;
        const w32::com::Result result = task->GetStatus(&status);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask,GetStatus,result);
        }
        return (status);
    }

}

namespace w32 { namespace ts {

    Status::Status ()
        : myValue(0)
    {
    }

    Status::Status ( const Task& task )
        : myValue( ::query(task.ptr().value()) )
    {
    }

    bool Status::scheduled () const
    {
        return ((myValue & SCHED_S_TASK_NOT_SCHEDULED) != 0);
    }

    bool Status::running () const
    {
        return ((myValue & SCHED_S_TASK_RUNNING) != 0);
    }

    bool Status::ready () const
    {
        return ((myValue & SCHED_S_TASK_READY) != 0);
    }

} }

