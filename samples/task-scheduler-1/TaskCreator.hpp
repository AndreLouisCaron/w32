#ifndef _TaskCreator_hpp__
#define _TaskCreator_hpp__

#include <w32.ts-1.hpp>
#include <iostream>
#include <string>

        /*!
         * @brief Create a new task, providing parameters using strings.
         */
    class TaskCreator
    {
        /* data. */
    private:
        w32::com::Library myContext;
        w32::ts::Scheduler myScheduler;
        w32::ts::Task myTask;
        w32::ts::Editor myEditor;

        /* construction. */
    public:
        TaskCreator ( const w32::string& name )
            : myContext(), myScheduler(),
              myTask(w32::ts::Task::create(myScheduler,name)),
              myEditor(myTask)
        {}

        /* methods. */
    private:
        static bool specifies (
            const w32::string& property, const w32::string& model
            )
        {
            return (::wcsncmp(property.data(),model.data(),model.size()) == 0);
        }

        /* operators. */
    public:
            /*!
             * @brief Set one of the tasks's properties.
             */
        void operator() ( const w32::string& property )
        {
            static const w32::string application(L"-application=");
            static const w32::string arguments(L"-arguments=");
            static const w32::string creator(L"-creator=");
            static const w32::string account(L"-account=");
            if ( specifies(property,application) ) {
                w32::string value = property.substr(application.length());
                myEditor.application(value);
            }
            else if ( specifies(property,arguments) ) {
                w32::string value = property.substr(arguments.length());
                myEditor.arguments(value);
            }
            else if ( specifies(property,account) ) {
                w32::string value = property.substr(account.length());
                myEditor.account(value);
            }
            else if ( specifies(property,creator) ) {
                w32::string value = property.substr(creator.length());
                myEditor.creator(value);
            }
            else {
                // Invalid argument.
                std::wcerr << L"Invalid proprety: " << property << std::endl;
            }
        }

            /*!
             * @brief Save the task.
             */
        void operator() () {
            myEditor.commit();
        }
    };

#endif /* _TaskCreator_hpp__ */
