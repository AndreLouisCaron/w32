// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ts-2/Action.hpp>

namespace w32 { namespace ts {

    const Action::Type Action::Type::command ()
    {
        return (TASK_ACTION_EXEC);
    }

    const Action::Type Action::Type::handler ()
    {
        return (TASK_ACTION_COM_HANDLER);
    }

    const Action::Type Action::Type::email ()
    {
        return (TASK_ACTION_SEND_EMAIL);
    }

    const Action::Type Action::Type::message ()
    {
        return (TASK_ACTION_SHOW_MESSAGE);
    }

    Action::Type Action::Type::of ( const Action& action )
    {
        ::TASK_ACTION_TYPE value = TASK_ACTION_EXEC;
        const com::Result result = action.ptr()->get_Type(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IAction, get_Type, result);
        }
        return (Type(value));
    }

    Action::Action ( ::IAction * object )
        : com::Wrapper< ::IAction >(object)
    {
    }

    Action::Type Action::type () const
    {
        return (Type::of(*this));
    }

    void Action::identifier ( const bstring& value )
    {
        const com::Result result = ptr()->put_Id(value.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IAction,put_Id,result);
        }
    }

    bstring Action::identifier () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_Id(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IAction, get_Id, result);
        }
        return (bstring(value));
    }

} }
