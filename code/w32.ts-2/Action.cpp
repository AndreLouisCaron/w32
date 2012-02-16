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
