// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-1/Scheduler.hpp>

namespace {

    ::ITaskScheduler * open ()
    {
        void * scheduler = 0;
        const w32::com::Result result = ::CoCreateInstance(
            CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER,
            IID_ITaskScheduler, &scheduler
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskScheduler,CoCreateInstance,result);
        }
        return (static_cast< ::ITaskScheduler* >(scheduler));
    }

}

namespace w32 { namespace ts {

    Scheduler::Scheduler ()
        : com::Wrapper< ::ITaskScheduler >( ::open() )
    {
    }

    void Scheduler::remove ( const string& task )
    {
        const w32::com::Result result = ptr()->Delete(task.data());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskScheduler,Delete,result);
        }
    }

} }
