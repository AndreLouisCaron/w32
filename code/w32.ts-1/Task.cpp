// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
