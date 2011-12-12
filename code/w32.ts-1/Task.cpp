// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ts-1/Task.hpp>
#include <w32.ts-1/Scheduler.hpp>
#include <w32/Reference.hpp>

namespace {

    void release ( wchar_t * object )
    {
        ::CoTaskMemFree(object);
    }

    typedef w32::Reference< wchar_t* > Buffer;

    Buffer claim ( wchar_t * object )
    {
        return (Buffer(object, &release));
    }

    ::ITask * create ( ::ITaskScheduler * scheduler, ::LPCWSTR name )
    {
        ::IUnknown * task = 0;
        const w32::com::Result result =
            scheduler->NewWorkItem(name, CLSID_CTask, IID_ITask, &task);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskScheduler, NewWorkItem, result);
        }
        return (reinterpret_cast<::ITask*>(task));
     }

    ::ITask * open ( ::ITaskScheduler * scheduler, ::LPCWSTR name )
    {
        ::IUnknown * task = 0;
        const w32::com::Result result =
            scheduler->Activate(name, IID_ITask, &task);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskScheduler,Activate,result);
        }
        return (reinterpret_cast<::ITask*>(task));
    }

}

namespace w32 { namespace ts {

    Task Task::create ( Scheduler& scheduler, const string& name )
    {
        return (Task( ::create(scheduler.ptr().value(), name.data()) ));
    }

    Task::Task ( const Ptr& task )
        : com::Wrapper< ::ITask >(task)
    {
    }

    Task::Task ( Scheduler& scheduler, const string& name )
        : com::Wrapper< ::ITask >(
              ::open(scheduler.ptr().value(), name.data())
              )
    {
    }

    string Task::application () const
    {
        wchar_t * string = 0;
        com::Result result = ptr()->GetApplicationName(&string);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask,GetApplicationName,result);
        }
        return (w32::string(::claim(string)));
    }

    string Task::creator () const
    {
        wchar_t * string = 0;
        const com::Result result = ptr()->GetCreator(&string);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask,GetCreator,result);
        }
        return (w32::string(::claim(string)));
    }

    string Task::account () const
    {
        wchar_t * string = 0;
        const com::Result result = ptr()->GetAccountInformation(&string);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask,GetAccountInformation,result);
        }
        return (w32::string(::claim(string)));
    }

    word Task::triggers () const
    {
        ::WORD count = 0;
        const com::Result result = ptr()->GetTriggerCount(&count);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask,GetTriggerCount,result);
        }
        return (count);
    }

} }
