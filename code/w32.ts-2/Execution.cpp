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

#include <w32.ts-2/Execution.hpp>
#include <w32.ts-2/Executions.hpp>
#include <w32.ts-2/State.hpp>
#include <w32/Variant.hpp>

namespace {

    ::IRunningTask * open ( ::IRunningTaskCollection * list, long name )
    {
        ::IRunningTask * task = 0;
        const w32::Variant index(name);
        const w32::com::Result result = list->get_Item(index.value(), &task);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTaskCollection, get_Item, result);
        }
        return (task);
    }

}

namespace w32 { namespace ts {

    Execution::Execution ( const Executions& list, long index )
        : com::Wrapper< ::IRunningTask >( ::open(list.ptr().value(), index) )
    {
    }

    State Execution::state () const
    {
        return (State::of(*this));
    }

    bstring Execution::name () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_Name(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTask,get_Name,result);
        }
        return (bstring(value));
    }

    bstring Execution::path () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_Path(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTask,get_Path,result);
        }
        return (bstring(value));
    }

    bstring Execution::handler () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_InstanceGuid(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTask,get_InstanceGuid,result);
        }
        return (bstring(value));
    }

    bstring Execution::action () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_CurrentAction(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTask,get_CurrentAction,result);
        }
        return (bstring(value));
    }

    void Execution::stop ()
    {
        const com::Result result = ptr()->Stop();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTask,Stop,result);
        }
    }

    void Execution::refresh ()
    {
        const com::Result result = ptr()->Refresh();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTask,Refresh,result);
        }
    }

} }
