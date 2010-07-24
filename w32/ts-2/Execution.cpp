// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-2/Execution.hpp>
#include <w32/ts-2/Executions.hpp>
#include <w32/ts-2/State.hpp>
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
