// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-2/State.hpp>
#include <w32/ts-2/Execution.hpp>
#include <w32/ts-2/Registration.hpp>

namespace w32 { namespace ts {

    const State State::unknown ()
    {
        return (TASK_STATE_UNKNOWN);
    }

    const State State::disabled ()
    {
        return (TASK_STATE_DISABLED);
    }

    const State State::queued ()
    {
        return (TASK_STATE_QUEUED);
    }

    const State State::ready ()
    {
        return (TASK_STATE_READY);
    }

    const State State::running ()
    {
        return (TASK_STATE_RUNNING);
    }

    State State::of ( const Execution& task )
    {
        ::TASK_STATE value = TASK_STATE_UNKNOWN;
        const com::Result result = task.ptr()->get_State(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTask,get_State,result);
        }
        return (State(value));
    }

    State State::of ( const Registration& task )
    {
        ::TASK_STATE value = TASK_STATE_UNKNOWN;
        const com::Result result = task.ptr()->get_State(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,get_State,result);
        }
        return (State(value));
    }

    State::State ( Value value )
        : myValue(value)
    {
    }

    State::Value State::value () const
    {
        return (myValue);
    }

    State::operator State::Value () const
    {
        return (myValue);
    }

    bool State::operator== ( const State& other ) const
    {
        return (myValue == other.myValue);
    }

    bool State::operator!= ( const State& other ) const
    {
        return (myValue != other.myValue);
    }

} }
