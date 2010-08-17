#ifndef _TaskRemover_hpp__
#define _TaskRemover_hpp__

#include <w32.ts-1.hpp>
#include <iostream>
#include <string>

        /*!
         * @brief Remove an existing task.
         */
    class TaskRemover
    {
        /* data. */
    private:
        w32::com::Library myContext;
        w32::ts::Scheduler myScheduler;

        /* construction. */
    public:
        TaskRemover ()
            : myContext(), myScheduler()
        {}

        /* operators. */
    public:
            /*!
             * @brief Remove the task using it's name.
             */
        void operator() ( const w32::string& task ) {
            myScheduler.remove(task);
        }
    };

#endif /* _TaskRemover_hpp__ */
