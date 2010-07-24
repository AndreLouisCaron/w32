#ifndef _TaskDetailPrinter_hpp__
#define _TaskDetailPrinter_hpp__

#include <w32.ts-1.hpp>
#include <iostream>
#include <string>

        /*!
         * @brief Print the details of one or more existing tasks.
         */
    class TaskDetailPrinter
    {
        /* data. */
    private:
        w32::com::Library myContext;
        w32::ts::Scheduler myScheduler;

        /* construction. */
    public:
        TaskDetailPrinter ()
            : myContext(), myScheduler()
        {}

        /* operators. */
    public:
            /*!
             * @brief Print the task's details using it's name.
             */
        void operator() ( const w32::string& taskName )
        {
            w32::ts::Task task(myScheduler,taskName);
            w32::ts::Status status(task);
            
            std::wcout
                << std::boolalpha
                << L"[Task]"                               << std::endl
                << L"  name="        << taskName           << std::endl
                << L"  creator="     << task.application() << std::endl
                << L"  application=" << task.application() << std::endl
                << L"  account="     << task.account()     << std::endl
                << L"  scheduled="   << status.scheduled() << std::endl
                << L"  running="     << status.running()   << std::endl
                << L"  ready="       << status.ready()     << std::endl;
            for ( w32::word i = 0; i < task.triggers(); ++i ) {
                w32::ts::Trigger trigger(task,i);
                std::wcout << L"  [Trigger]" << std::endl;
                std::wcout << L"    type=" << trigger.type() << std::endl;
            }
        }

            /*!
             * @brief Print the details of all registered tasks.
             */
        void operator() ()
        {
            w32::ts::Tasks tasks(myScheduler);
            for ( w32::string name; tasks.next(name); ) {
                (*this)(name);
            }
        }
    };

#endif /* _TaskDetailPrinter_hpp__ */
