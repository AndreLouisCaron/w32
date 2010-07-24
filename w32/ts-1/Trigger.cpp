// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-1/Trigger.hpp>
#include <w32/ts-1/Task.hpp>
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
