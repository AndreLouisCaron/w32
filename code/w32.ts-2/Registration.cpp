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

#include <w32.ts-2/Registration.hpp>
#include <w32.ts-2/Definition.hpp>
#include <w32.ts-2/Folder.hpp>
#include <w32.ts-2/Registrations.hpp>
#include <w32.ts-2/State.hpp>
#include <w32/Variant.hpp>

namespace {

    ::IRegisteredTask * register_ (
        ::ITaskFolder * folder, ::ITaskDefinition * definition
        )
    {
        const w32::bstring path(L"");
        const w32::Variant account;
        const w32::Variant password;
        const w32::Variant token;
        ::IRegisteredTask * task = 0;
        const w32::com::Result result = folder->RegisterTaskDefinition(
            path.value(), definition, TASK_CREATE_OR_UPDATE, account.value(),
            password.value(), TASK_LOGON_INTERACTIVE_TOKEN, token.value(), &task
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IFolder,RegisterTaskDefinition,result);
        }
        return (task);
    }

    ::IRegisteredTask * open ( ::IRegisteredTaskCollection * tasks, long index )
    {
        const w32::Variant identifier(index);
        ::IRegisteredTask * task = 0;
        const w32::com::Result result =
            tasks->get_Item(identifier.value(), &task);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTaskCollection,,result);
        }
        return (task);
    }

}

namespace w32 { namespace ts {

    Registration::Registration ( Folder& folder, Definition& task )
        : com::Wrapper< ::IRegisteredTask >(
            ::register_(folder.ptr().value(), task.ptr().value())
            )
    {
    }

    Registration::Registration ( Registrations& tasks, long index )
        : com::Wrapper< ::IRegisteredTask >( ::open(tasks.ptr().value(),index) )
    {
    }

    bstring Registration::name () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_Name(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,get_Name,result);
        }
        return (bstring(value));
    }

    bstring Registration::path () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_Path(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,get_Path,result);
        }
        return (bstring(value));
    }

    bstring Registration::xml () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_Xml(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,get_Xml,result);
        }
        return (bstring(value));
    }

    State Registration::state () const
    {
        return (State::of(*this));
    }

    bool Registration::enabled () const
    {
        ::VARIANT_BOOL value = VARIANT_FALSE;
        const com::Result result = ptr()->get_Enabled(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,get_Enabled,result);
        }
        return (value == VARIANT_TRUE);
    }

    void Registration::enabled ( bool activate )
    {
        const ::VARIANT_BOOL value = (activate)? VARIANT_TRUE : VARIANT_FALSE;
        const com::Result result = ptr()->put_Enabled(value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,put_Enabled,result);
        }
    }

    void Registration::enable ()
    {
        const com::Result result = ptr()->put_Enabled(VARIANT_TRUE);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,put_Enabled,result);
        }
    }

    void Registration::disable ()
    {
        const com::Result result = ptr()->put_Enabled(VARIANT_FALSE);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,put_Enabled,result);
        }
    }


    void Registration::stop ()
    {
        const com::Result result = ptr()->Stop(0);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,put_Enabled,result);
        }
    }

} }
