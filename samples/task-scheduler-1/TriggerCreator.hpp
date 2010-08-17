#ifndef _TriggerCreator_hpp__
#define _TriggerCreator_hpp__

#include <w32.hpp>
#include <w32.ts-1.hpp>
#include <iostream>
#include <sstream>
#include <string>

        /*!
         * @brief Create a new trigger for an exising task.
         */
    class TriggerCreator
    {
        /* data. */
    private:
        w32::com::Library myContext;
        w32::ts::Scheduler myScheduler;
        w32::ts::Task myTask;
        w32::ts::Editor myTaskEditor;
        w32::ts::Trigger myTrigger;
        w32::ts::Trigger::Editor myEditor;

        /* construction. */
    public:
            /*!
             * @brief Create a trigger for a task, using it's name.
             */
        TriggerCreator ( const w32::string& task )
            : myContext(), myScheduler(), myTask(myScheduler, task),
              myTaskEditor(myTask), myTrigger(myTask), myEditor(myTrigger)
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
             * @brief Set one of the trigger's property, using a string.
             */
        void operator() ( const w32::string& property )
        {
            static const w32::string begin(L"-begin=");
            static const w32::string daily(L"-daily=");
            if ( specifies(property,begin) ) {
                std::wstringstream parser;
                parser << property.substr(begin.length());
                int year = 0, month = 0, day = 0;
                if ( parser.str() == L"today" ) {
                    w32::Time time;
                    year = time.year(), month = time.month(), day = time.day();
                }
                else {
                    if ( !(parser >> year) || (year < 2008) ) {
                        std::cerr << "Invalid year." << std::endl;
                    }
                    if ( parser.get() != int('/') ) {
                        std::cerr << "Invalid trigger format." << std::endl;
                    }
                    if ( !(parser >> month) || (month < 1) || (month > 12) ) {
                        std::cerr << "Invalid month." << std::endl;
                    }
                    if ( parser.get() != int('/') ) {
                        std::cerr << "Invalid trigger format." << std::endl;
                    }
                    if ( !(parser >> day) || (day < 1) || (day > 31) ) {
                        std::cerr << "Invalid day." << std::endl;
                    }
                }
                myEditor.start(year,month,day);
            }
            else if ( specifies(property,daily) ) {
                std::wstringstream parser;
                parser << property.substr(daily.length());
                int interval = 0;
                if ( !(parser >> interval) || (interval < 0) ) {
                    std::cerr << "Invalid interval." << std::endl;
                }
                if ( parser.get() != int(',') ) {
                    std::cerr << "Invalid trigger format." << std::endl;
                }
                int hour = 0;
                if ( !(parser >> hour) || (hour < 0) || (hour > 23) ) {
                    std::cerr << "Invalid hour." << std::endl;
                }
                if ( parser.get() != int(':') ) {
                    std::cerr << "Invalid trigger format." << std::endl;
                }
                int minute = 0;
                if ( !(parser >> minute) || (minute < 0) || (minute > 59) ) {
                    std::cerr << "Invalid minute." << std::endl;
                }
                myEditor.daily(interval,hour,minute);
            }
        }

            /*!
             * @brief Save the trigger (and the task).
             */
        void operator() ()
        {
            myEditor.commit();
            myTaskEditor.commit();
        }
    };

#endif /* _TriggerCreator_hpp__ */
