#ifndef _TaskNamePrinter_hpp__
#define _TaskNamePrinter_hpp__

#include <w32.ts-1.hpp>
#include <iostream>

        /*!
         * @brief Print the names of all registered tasks.
         */
    class TaskNamePrinter
    {
        /* data. */
    private:
        w32::com::Library myContext;
        w32::ts::Scheduler myScheduler;

        /* construction. */
    public:
        TaskNamePrinter ()
            : myContext(), myScheduler()
        {}

        /* operators. */
    public:
        void operator() ()
        {
            w32::ts::Tasks tasks(myScheduler);
            for ( w32::string name; tasks.next(name); ) {
                std::wcout << name.c_str() << std::endl;
            }
        }
    };

#endif /* _TaskNamePrinter_hpp__ */
