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

#include <w32.ts-1/Trigger.hpp>
#include <w32.ts-1/Task.hpp>
#include <iostream>

namespace {

    ::ITaskTrigger * open ( ::ITask * task, const WORD& index )
    {
        ::ITaskTrigger * trigger = 0;
        const w32::com::Result result = task->GetTrigger(index,&trigger);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask, GetTrigger, result);
        }
        return (trigger);
    }

    ::ITaskTrigger * create ( ::ITask * task )
    {
        ::ITaskTrigger * trigger = 0;
        ::WORD index = 0;
        const w32::com::Result result = task->CreateTrigger(&index,&trigger);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITask, CreateTrigger, result);
        }
        return (trigger);
    }

}

namespace w32 { namespace ts {

    const Trigger::Type Trigger::Type::once ()
    {
        return (TASK_TIME_TRIGGER_ONCE);
    }

    const Trigger::Type Trigger::Type::daily ()
    {
        return (TASK_TIME_TRIGGER_DAILY);
    }

    const Trigger::Type Trigger::Type::weekly ()
    {
        return (TASK_TIME_TRIGGER_WEEKLY);
    }

    const Trigger::Type Trigger::Type::idle ()
    {
        return (TASK_EVENT_TRIGGER_ON_IDLE);
    }

    const Trigger::Type Trigger::Type::start ()
    {
        return (TASK_EVENT_TRIGGER_AT_SYSTEMSTART);
    }

    const Trigger::Type Trigger::Type::logon ()
    {
        return (TASK_EVENT_TRIGGER_AT_LOGON);
    }

    std::ostream& operator<<
        ( std::ostream& out, const Trigger::Type& type )
    {
        if ( type == Trigger::Type::daily() ) {
            return (out <<  "daily");
        }
        return (out << "unknown");
    }

    std::wostream& operator<<
        ( std::wostream& out, const Trigger::Type& type )
    {
        if ( type == Trigger::Type::daily() ) {
            return (out <<  L"daily");
        }
        return (out << L"unknown");
    }

    Trigger::Editor::Editor ( Trigger& trigger )
        : myTrigger(trigger), myData(myTrigger.myData.get())
    {
    }

    void Trigger::Editor::start ( int year, int month, int day )
    {
        myData.wBeginYear = year;
        myData.wBeginMonth = month;
        myData.wBeginDay = day;
    }

    void Trigger::Editor::daily ( ::WORD interval, int hour, int month )
    {
        myData.TriggerType = TASK_TIME_TRIGGER_DAILY;
        myData.Type.Daily.DaysInterval = interval;
        myData.wStartHour = hour;
        myData.wStartMinute = month;
    }

    void Trigger::Editor::commit () const
    {
        const com::Result result = myTrigger.ptr()->SetTrigger(&myData);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskTrigger,SetTrigger,result);
        }
    }

    Trigger::Data::Data ( ::ITaskTrigger& trigger )
    {
        ::ZeroMemory(&myValue,sizeof(myValue));
        myValue.cbTriggerSize = sizeof(myValue);
        const com::Result result = trigger.GetTrigger(&myValue);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITrigger,GetTrigger,result);
        }
    }

    Trigger::Data::Data ()
    {
        ::ZeroMemory(&myValue,sizeof(myValue));
        myValue.cbTriggerSize = sizeof(myValue);
    }

    ::TASK_TRIGGER& Trigger::Data::get ()
    {
        return (myValue);
    }

    const ::TASK_TRIGGER& Trigger::Data::get () const
    {
        return (myValue);
    }

    Trigger::Trigger ( const Task& task )
        : com::Wrapper< ::ITaskTrigger >( ::create(task.ptr().value()) )
    {
    }

    Trigger::Trigger ( const Task& task, const ::WORD& index )
        : com::Wrapper< ::ITaskTrigger >(
              ::open(task.ptr().value(),index)
              ),
          myData( *ptr() )
    {
    }

    const Trigger::Type Trigger::type () const
    {
        return (Type(myData.get().TriggerType));
    }

} }
